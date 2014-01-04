//
//  RenderingEngine1.cpp
//  HelloArrow
//
//  Created by 林光海 on 13-12-27.
//  Copyright (c) 2013年 JackLinMaker. All rights reserved.
//

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.hpp"

static const float RevolutionsPerSecond = 1;

class RenderingEngine1 : public IRenderingEngine {
public:
    RenderingEngine1();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
private:
    float RotationDirection() const;
    float m_desiredAngle;
    float m_currentAngle;
    GLuint m_frameBuffer;
    GLuint m_renderBuffer;
};

IRenderingEngine* CreateRenderer1()
{
    return new RenderingEngine1();
}

struct Vertex {
    float Position[2];
    float Color[4];
};

const Vertex Vetices[] = {
    {{-0.5, -0.866}, {1, 1, 0.5f, 1}},
    {{0.5, -0.866},  {1, 1, 0.5f, 1}},
    {{0, 1},         {1, 1, 0.5f, 1}},
    {{-0.5, -0.866}, {0.5f, 0.5f, 0.5f}},
    {{0.5, -0.866},  {0.5f, 0.5f, 0.5f}},
    {{0, -0.4f},     {0.5f, 0.5f, 0.5f}},
};

RenderingEngine1::RenderingEngine1()
{
    glGenRenderbuffersOES(1, &m_renderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderBuffer);
}

void RenderingEngine1::Initialize(int width, int height)
{
    glGenFramebuffersOES(1, &m_frameBuffer);
    glBindRenderbufferOES(GL_FRAMEBUFFER_OES, m_frameBuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_renderBuffer);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    
    const float maxX = 2;
    const float maxY = 3;
    glOrthof(-maxX, +maxX, -maxY, +maxY, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    OnRotate(DeviceOrientationPortrait);
    m_currentAngle = m_desiredAngle;
}

void RenderingEngine1::Render() const
{
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(m_currentAngle, 0, 0, 1);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vetices[0].Position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vetices[0].Color[0]);
    
    GLsizei vertexCount = sizeof(Vetices) / sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glPopMatrix();
}

void RenderingEngine1::OnRotate(DeviceOrientation newOrientation)
{
    float angle = 0;
    
    switch (newOrientation) {
        case DeviceOrientationLandscapeLeft:
            angle = 270;
            break;
        case DeviceOrientationPortraitUpsideDown:
            angle = 180;
            break;
        case DeviceOrientationLandscapeRight:
            angle = 90;
            break;
        default:
            break;
    }
    
    m_desiredAngle = angle;
}

void RenderingEngine1::UpdateAnimation(float timeStep)
{
    float direction = RotationDirection();
    if(direction == 0)
        return;
    float degrees = timeStep * 360 * RevolutionsPerSecond;
    m_currentAngle += degrees * direction;
    
    // Ensure that the angle stays within [0, 360)
    if(m_currentAngle >= 360)
        m_currentAngle -= 360;
    else if(m_currentAngle < 0)
        m_currentAngle += 360;
    
    // if the rotation direction changed, then we overshot the desired angle.
    if(RotationDirection() != direction)
        m_currentAngle = m_desiredAngle;
}

float RenderingEngine1::RotationDirection() const
{
    float delta = m_desiredAngle - m_currentAngle;
    if(delta == 0)
        return 0;
    
    bool counterclockwise = ((delta > 0 && delta <= 180) || (delta < -180));
    return counterclockwise ? +1 : -1;
}
