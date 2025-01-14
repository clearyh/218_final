//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "render.h"
#include "scan.h"
#include "ui.h"
#include "system.h"
#include "tft.h"
#include "pc_serial_com.h"

//=====[Declaration of private defines]========================================

#define VREF 3.3
#define V1 0.3 // V1, V2, I2, and I1 are datapoints for the linear model to convert sensor voltage to a distance.
#define V2 2.01
#define I1 .024
#define I2 0.155
#define M (I2 - I1)/(V2 - V1)
#define R_SENSOR 15.25 // The distance on xy plane of the sensor from the center of rotation
#define SENSOR_DZ 3 // variable for the downward tilt of the sensor
#define CAMERA_FOV_X 68 // camera fov on 2 axes in degrees - note 68/90 ~= 240/320, the display aspect ratio
#define CAMERA_FOV_Z 90


//=====[Declaration of private data types]=====================================

Vector virtualCameraPosition(20, 0, 20); // setting position and direction of virtual camera
Vector virtualCameraDirection_X(-1, 0, 0);
Vector virtualCameraDirection(-1, 0, -0.5);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static Vector getSensorPosition(int t_s, int z_s); 
// gets 3D coordinate of sensor for a certain theta and Z
static Vector getSensorDirection(int t_s, int z_s);
// gets 3D coordinate of sensor direction for a certain theta and Z
static Vector getSurfacePoint(int t_s, int z_s);
//gets 3D coordinate of a point on the target objects surface for a certain theta and Z


//gets a color for the renderer based on distance
static uint16_t getColor(float dist);


//=====[Implementations of public functions]===================================


//function to render data to the screen
void render() {
    int z_res = getZres();
    int t_res = getTres();
    for(int z_step = 0; z_step < z_res; z_step++) { // iterate through Z
        for(int theta_step = 0; theta_step < t_res; theta_step++) { // iterate through theta
            Vector surface_point = getSurfacePoint(theta_step, z_step);
            Vector point_to_camera = surface_point.diff(virtualCameraPosition);
            float cameraDistance = point_to_camera.magnitude();
            Vector ptc_X(point_to_camera.x, point_to_camera.y, 0);
            float angle_x = ptc_X.angle(virtualCameraDirection_X);
            if (point_to_camera.y > 0) angle_x = -angle_x;
            angle_x += 34;
            float x_screen_proportion = angle_x / CAMERA_FOV_X;
            if (x_screen_proportion >= 0 && x_screen_proportion <= 1) {
                uint16_t xP = (uint16_t)(x_screen_proportion * 240);
                Vector ptc_Z(point_to_camera.x, 0, point_to_camera.z);
                ptc_Z.normalize();
                virtualCameraDirection.normalize();
                float angle_z = ptc_Z.angle(virtualCameraDirection);
                if (ptc_Z.z < virtualCameraDirection.z) angle_z = -angle_z;
                angle_x += 45;
                float z_screen_proportion = angle_z / CAMERA_FOV_Z;
                if (z_screen_proportion >= 0 && z_screen_proportion <= 1) {
                    uint16_t yP = (uint16_t)(z_screen_proportion * 320);
                    uint16_t color = getColor(cameraDistance);
                    tftShadePixel(xP, yP, color);
                }
            }
        }
    }
    while (!readEnter()) {

    }
    tftShadeRect(0, 0, 240, 320, 0x0000);
    mainMenu();
}


//transmit an array of the 3D surface point coordinates in human readable ASCII over uartUSB
void transmit() { 
    tftDrawCenteredString(120, 100, TXT_HEAD, "transmitting", 12);
    int z_res = getZres();
    int t_res = getTres();
    char *openparen = "(";
    char *closeparen = ")";
    char *comma = ",";
    uartWriteString("[", 1);
    for(int z_step = 0; z_step < z_res; z_step++) { // iterate through Z
        for(int theta_step = 0; theta_step < t_res; theta_step++) { // iterate through theta
            uartWriteString(comma, 1);
            uartWriteString(openparen, 1);
            Vector surface_point = getSurfacePoint(theta_step, z_step);
            char float_string[5];
            sprintf(float_string, "%.2f", surface_point.x); // transmit ,(x, y, z)
            uartWriteString(float_string, 7);
            uartWriteString(comma, 1);
            sprintf(float_string, "%.2f", surface_point.y);
            uartWriteString(float_string, 7);
            uartWriteString(comma, 1);
            sprintf(float_string, "%.2f", surface_point.z);
            uartWriteString(float_string, 7);
            uartWriteString(closeparen, 1);
        }
    }
    uartWriteString("]", 1);
    tftDrawCenteredString(120, 100, TXT_HEAD, "transmission", 12);
    tftDrawCenteredString(120, 140, TXT_HEAD, "complete", 8);
    while (!readEnter()) {

    }
    tftShadeRect(0, 100, 240, 180, 0x0000);
    mainMenu();
}

//=====[Implementations of private functions]==================================


//gets a floating point distance in centimeters for a certain analogIn uint16_t data
float getDistance(int t_s, int z_s) {
    uint16_t sensor_reading = getSensorReading(t_s, z_s);
    float voltage = VREF * (1.0 * sensor_reading / UINT16_MAX);
    float inverse = (voltage - V1) * M + I1;
    float ret = (1.0 / inverse) - 0.42;
    return ret;
}

static Vector getSurfacePoint(int t_s, int z_s) {
    Vector sensor_pos = getSensorPosition(t_s, z_s);
    Vector sensor_dir = getSensorDirection(t_s, z_s);
    float distance = getDistance(t_s, z_s);
    sensor_dir.scale(distance);
    return sensor_pos.sum(sensor_dir);
}

static Vector getSensorPosition(int t_s, int z_s) {
    //uses trig to create 3D vector for sensor position for a certain theta and z 
    float theta = 3.1415926 * 2 * t_s / getTres();
    float v_z = 12.0 * z_s / getZres();
    float v_x = R_SENSOR * cos(theta);
    float v_y = R_SENSOR * sin(theta);
    return Vector(v_x, v_y, v_z);
}

static Vector getSensorDirection(int t_s, int z_s) {
    // because the sensor is always pointing towards the center, the direction is -1*position on the xy plane.
    // macro SENSOR_DZ is used to represent the downward angle of the sensor. it must be calibrated experimentally.
    Vector v = getSensorPosition(t_s, z_s);
    v.scale(-1);
    v.z = -SENSOR_DZ;
    v.normalize();
    return v;
}

static uint16_t getColor(float dist) {
    float c_f = dist * 63 / 40;
    if (c_f < 0) c_f = 0;
    if (c_f > 63) c_f = 63;
    uint16_t c_i = (uint16_t) c_f;
    uint16_t color = c_i;
    color = (color & (c_i << 5));
    color = (color & (c_i << 11));
    return color;
    
}

Vector::Vector(float x0, float y0, float z0) {
    x = x0;
    y = y0;
    z = z0;
}

float Vector::magnitude() {
    return sqrt(x*x + y*y + z*z);
}

float Vector::dot(Vector v) {
    return (v.x * x + v.y * y + v.z * z);
}

Vector Vector::sum(Vector v) {
    return Vector(v.x + x, v.y + y, v.z + z);
}

Vector Vector::diff(Vector v) {
    return Vector(x - v.x, y -v.y, z - v.z);
}

Vector Vector::cross(Vector v) {
    return Vector ((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
}

void Vector::normalize() {
    float m = magnitude();
    x = x/m;
    y = y/m;
    z = z/m;
}

void Vector::scale(float k) {
    x = x*k;
    y = y*k;
    z = z*k;
}

float Vector::angle(Vector v) {
    float m1 = magnitude();
    float m2 = v.magnitude();
    float den = m1*m2;
    float num = dot(v);
    return acos(num/den);
}