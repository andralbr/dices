#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

enum Action
{
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    PITCH_UP,
    PITCH_DOWN,
    YAW_RIGHT,
    YAW_LEFT,
    ROLL_RIGHT,
    ROLL_LEFT
};

class Camera
{
    private:

        float m_speed;

        glm::vec3 m_position; // camera position
        glm::vec3 m_vz;   // camera z (= (-1) view)
        glm::vec3 m_vy;   // camera up
        glm::vec3 m_vx;   // camera right vector

        glm::vec3 m_vz_temp;
        glm::vec3 m_vy_temp;
        glm::vec3 m_vx_temp;

        float m_pitch;
        float m_yaw;
        float m_roll;


    public:
    Camera() : m_vz( glm::vec3(0.0f, 0.0f, 1.0f) ), m_vy( glm::vec3(0.0f, 1.0f, 0.0f) ), m_vx( glm::vec3(1.0f, 0.0f, 0.0f) ), m_position( glm::vec3(0.0f, 0.0f, 3.0f)), m_speed(1.0f)
    {       
    }

    Camera(float speed) : m_speed(speed)
    {        
    }

    Camera(glm::vec3 viewpoint, glm::vec3 upvector, float speed = 1.0f, glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f) ) : m_speed(speed), m_position(position) 
    {
        m_vz = glm::normalize(m_position - viewpoint);
        m_vx = glm::normalize(glm::cross(upvector, m_vz));
        m_vy = glm::cross(m_vz, m_vx);
    }


    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(m_position, m_position - m_vz, m_vy);   // form (position, viewpoint, up-vector)
                                                        
    }

    glm::vec3 getPosition()
    {
        return m_position;
    }


    void processKeyboard(Action action, float dtime)
    {
        
        if (action == MOVE_FORWARD)
        {
            m_position -= (m_speed * dtime) * m_vz;    // ! in negative z axis 
        }

        if (action == MOVE_BACKWARD)
        {
            m_position += (m_speed * dtime) * m_vz;    
        }

        if (action == MOVE_RIGHT)
        {
            m_position += (m_speed * dtime) * m_vx; 
        }

        if (action == MOVE_LEFT)
        {
            m_position -= (m_speed * dtime) * m_vx; 
        }       
        
        if (action == PITCH_UP)
        {
            m_pitch = m_speed * dtime;
            m_vy_temp = cos(m_pitch) * m_vy + sin(m_pitch) * m_vz;
            m_vz_temp = -sin(m_pitch) * m_vy + cos(m_pitch) * m_vz;

            m_vy = m_vy_temp;
            m_vz = m_vz_temp;
        }

        if (action == PITCH_DOWN)
        {
            m_pitch = -m_speed * dtime;
            m_vy_temp = cos(m_pitch) * m_vy + sin(m_pitch) * m_vz;
            m_vz_temp = -sin(m_pitch) * m_vy + cos(m_pitch) * m_vz;

            m_vy = m_vy_temp;
            m_vz = m_vz_temp;
        }
  
        if (action == YAW_RIGHT)
        {
            m_yaw = m_speed * dtime;
            m_vx_temp = cos(m_yaw) * m_vx + sin(m_yaw) * m_vz;
            m_vz_temp = -sin(m_yaw) * m_vx + cos(m_yaw) * m_vz;

            m_vx = m_vx_temp;
            m_vz = m_vz_temp;
        }

        if (action == YAW_LEFT)
        {
            m_yaw = -m_speed * dtime;
            m_vx_temp = cos(m_yaw) * m_vx + sin(m_yaw) * m_vz;
            m_vz_temp = -sin(m_yaw) * m_vx + cos(m_yaw) * m_vz;

            m_vx = m_vx_temp;
            m_vz = m_vz_temp;
        }

        if (action == ROLL_RIGHT)
        {
            m_roll = m_speed * dtime;
            m_vx_temp = cos(m_roll) * m_vx - sin(m_roll) * m_vy;
            m_vy_temp = sin(m_roll) * m_vx + cos(m_roll) * m_vy;

            m_vx = m_vx_temp;
            m_vy = m_vy_temp;
        }    

        if (action == ROLL_LEFT)
        {
            m_roll = -m_speed * dtime;
            m_vx_temp = cos(m_roll) * m_vx - sin(m_roll) * m_vy;
            m_vy_temp = sin(m_roll) * m_vx + cos(m_roll) * m_vy;

            m_vx = m_vx_temp;
            m_vy = m_vy_temp;
        }               

    }



};




#endif