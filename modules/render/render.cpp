//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "render.h"
#include "scan.h"
#import "tft.h"

//=====[Declaration of private defines]========================================

#define VREF 3.3
#define V1 0.3
#define V2 2.01
#define I1 .024
#define I2 0.155
#define M (I2 - I1)/(V2 - V1)
#define R_SCANNER 20
#define SENSOR_DIR_Z 10
#define CAMERA_FOV_X 68
#define CAMERA_FOV_Y 90


//=====[Declaration of private data types]=====================================

int theta_step = 0;
int z_step = 0;

Vector virtualCameraPosition(20, 0, 20);
Vector virtualCameraDirection(-1, 0, -.5);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static Vector getSensorPosition(int t_s, int z_s);
static Vector getSensorDirection(int t_s, int z_s);
static float getDistance(int t_s, int z_s);
static void renderPoint(int t_s, int z_s);


//=====[Implementations of public functions]===================================

void render() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    for(int z_step = 0; z_step < Z_RESOLUTION; z_step++) {
        for(int theta_step = 0; theta_step < THETA_RESOLUTION; theta_step++) {
            Vector sensor_pos = getSensorPosition(theta_step, z_step);
            Vector sensor_dir = getSensorDirection(theta_step, z_step);
            float distance = getDistance(theta_step, z_step);
            sensor_dir.scale(distance);
            Vector surface_point = sensor_pos.sum(sensor_dir);
            Vector point_to_camera = virtualCameraPosition.diff(surface_point);
            float cameraDistance = point_to_camera.magnitude();


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
