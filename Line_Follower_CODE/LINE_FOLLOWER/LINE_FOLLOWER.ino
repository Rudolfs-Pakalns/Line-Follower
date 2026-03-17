/**
 * Line Follower with Trap Protection
 */

#include "GPIO.h"
#include "MOVEMENTS.h"

#define ARRAY_SIZE 5
#define BASE_SPEED 245
#define START_TIME 3000
#define PID_INTERVAL 2

uint8_t sensors[ARRAY_SIZE] = {SENSOR_1,SENSOR_2,SENSOR_3,SENSOR_4,SENSOR_5};
uint8_t sensor_reads[ARRAY_SIZE];

// stronger weights for faster recovery
int8_t weights[ARRAY_SIZE] = {-6,-3,0,3,6};

float error = 0;
float last_error = 0;
float filtered_error = 0;
float D = 0;

float kP = 48;
float kD = 25;

bool robot_running = false;

static bool last_button_state = HIGH;
static unsigned long last_press_time = 0;

unsigned long junction_lock = 0;


// prototypes
void Read_Sensors(uint8_t*,uint8_t*);
float calculate_error(uint8_t*,int8_t*);


void setup()
{
    GPIO_Init();
}


void loop()
{
    // ---------- Button ----------
    bool current_button_state = digitalRead(BUTTON);

    if(!current_button_state && last_button_state && millis()-last_press_time>200)
    {
        Stop_Motors();
        delay(START_TIME);
        robot_running = !robot_running;
        last_press_time = millis();
    }

    last_button_state = current_button_state;

    if(!robot_running)
    {
        Stop_Motors();
        return;
    }


    // ---------- PID timing ----------
    static unsigned long lastPID = 0;
    if(millis()-lastPID < PID_INTERVAL) return;
    lastPID = millis();


    // ---------- Read sensors ----------
    Read_Sensors(sensors,sensor_reads);


    // ---------- Center priority filter ----------
    if(sensor_reads[2] == 1)
    {
        sensor_reads[0] = 0;
        sensor_reads[4] = 0;
    }


    // ---------- Count active sensors ----------
    uint8_t active = 0;
    for(uint8_t i=0;i<ARRAY_SIZE;i++)
        active += sensor_reads[i];


    // ---------- Calculate error ----------
    error = calculate_error(sensor_reads, weights);
    error *= 1.2;


    // ---------- Strong 90° corner detection ----------
    if(sensor_reads[0] && sensor_reads[1] && !sensor_reads[2])
        error = -5;

    if(sensor_reads[3] && sensor_reads[4] && !sensor_reads[2])
        error = 5;


    // ---------- Smooth error ----------
    filtered_error = 0.5*filtered_error + 0.5*error;
    error = filtered_error;


    // ---------- Deadband ----------
    if(abs(error) < 0.35)
        error = 0;


    // ---------- Junction lock ----------
    if(active >= 4)
        junction_lock = millis();

    if(millis() - junction_lock < 120)
        error = last_error;


    // ---------- PID ----------
    float derivative = (error-last_error)/(PID_INTERVAL*0.001);

    D = 0.75*D + 0.25*derivative;

    float correction = kP*error + kD*D;

    correction = constrain(correction,-220,220);

    last_error = error;


    // ---------- Dynamic base speed ----------
    int base = BASE_SPEED - abs(error)*32;
    base = constrain(base,140,BASE_SPEED);


    // ---------- Motor speeds ----------
    int16_t left_speed  = base + correction;
    int16_t right_speed = base - correction;


    // ---------- Corner assist ----------
    if(abs(error) > 3)
    {
        left_speed  = base + correction*1.25;
        right_speed = base - correction*1.25;
    }


    // ---------- Center boost ----------
    if(sensor_reads[0]==0 &&
       sensor_reads[1]==0 &&
       sensor_reads[2]==1 &&
       sensor_reads[3]==0 &&
       sensor_reads[4]==0)
    {
        left_speed  = 255;
        right_speed = 255;
    }


    left_speed  = constrain(left_speed,-255,255);
    right_speed = constrain(right_speed,-255,255);


    // ---------- Motor control ----------
    if(left_speed >= 0)
        Left_Motor_Forward(MOTOR_PIN_B1,MOTOR_PIN_B2,left_speed);
    else
        Left_Motor_Reverse(MOTOR_PIN_B1,MOTOR_PIN_B2,-left_speed);

    if(right_speed >= 0)
        Right_Motor_Forward(MOTOR_PIN_A1,MOTOR_PIN_A2,right_speed);
    else
        Right_Motor_Reverse(MOTOR_PIN_A1,MOTOR_PIN_A2,-right_speed);
}



float calculate_error(uint8_t *sensors,int8_t *weights)
{
    int16_t weighted_sum = 0;
    int16_t sensor_sum = 0;

    for(uint8_t i=0;i<ARRAY_SIZE;i++)
    {
        weighted_sum += sensors[i]*weights[i];
        sensor_sum += sensors[i];
    }

    if(sensor_sum==0)
        return constrain(last_error*1.2,-4,4);

    return (float)weighted_sum / sensor_sum;
}


void Read_Sensors(uint8_t *sensor_array,uint8_t *sensor_reads)
{
    for(uint8_t i=0;i<ARRAY_SIZE;i++)
        sensor_reads[i] = digitalRead(sensor_array[i]);
}