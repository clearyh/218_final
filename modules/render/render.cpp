//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "render.h"
#include "scan.h"
#import "tft.h"

//=====[Declaration of private defines]========================================

#define VREF 3.3
#define V1 0.3 // V1, V2, I2, and I1 are datapoints for the linear model to convert sensor voltage to a distance.
#define V2 2.01
#define I1 .024
#define I2 0.155
#define M (I2 - I1)/(V2 - V1)
#define R_SCANNER 20 // The distance on xy plane of the sensor from the center of rotation
#define SENSOR_DZ 10 // variable for the downward tilt of the sensor
#define CAMERA_FOV_X 68 // camera fov on 2 axes in degrees - note 68/90 ~= 240/320, the display aspect ratio
#define CAMERA_FOV_Z 90


//=====[Declaration of private data types]=====================================

Vector virtualCameraPosition(20, 0, 20);
Vector virtualCameraDirection_X(-1, 0, 0);
Vector virtualCameraDirection(-1, 0, -0.5);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static Vector getSensorPosition(int t_s, int z_s);
static Vector getSensorDirection(int t_s, int z_s);
static Vector getSurfacePoint(int t_s, int z_s);
static float getDistance(int t_s, int z_s);
static uint16_t getColor(float dist);


//=====[Implementations of public functions]===================================

void render() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    for(int z_step = 0; z_step < Z_RESOLUTION; z_step++) { // iterate through Z
        for(int theta_step = 0; theta_step < THETA_RESOLUTION; theta_step++) { // iterate through theta
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
}

//=====[Implementations of private functions]==================================

static float getDistance(int t_s, int z_s) {
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
    return Vector(0, 0, 0);
}

static Vector getSensorDirection(int t_s, int z_s) {

    return Vector(0, 0, 0);
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