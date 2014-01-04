//
//  GLView.m
//  HelloArrow
//
//  Created by 林光海 on 13-12-26.
//  Copyright (c) 2013年 JackLinMaker. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import <mach/mach_time.h>
#import <OpenGLES/ES2/gl.h>

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer *)super.layer;
        eaglLayer.opaque = YES;
        
        m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if(!m_context || ![EAGLContext setCurrentContext:m_context]) {
            //[self release];
            return nil;
        }
        
        m_renderingEngine = CreateRenderer1();
        
        //GLuint frameBuffer, renderBuffer;
        //glGenFramebuffersOES(1, &frameBuffer);
        //glGenRenderbuffersOES(1, &renderBuffer);
        
        //glBindFramebufferOES(GL_FRAMEBUFFER_OES, frameBuffer);
        //glBindRenderbufferOES(GL_RENDERBUFFER_OES, renderBuffer);
        
        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        //glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, renderBuffer);
        
        //glViewport(0, 0, CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        [self drawView:nil];
        
        //[self drawView];
        
        m_timestamp = CACurrentMediaTime();
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate) name:UIDeviceOrientationDidChangeNotification object:nil];
    }
    return self;
}

- (void) didRotate:(NSNotification *)notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_renderingEngine->OnRotate((DeviceOrientation) orientation);
    [self drawView:nil];
}


+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (void) drawView:(CADisplayLink *)displayLink
{
    if(displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAnimation(elapsedSeconds);
    }
    
    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) dealloc
{
    if([EAGLContext currentContext] == m_context)
        [EAGLContext setCurrentContext:nil];
    
    //[m_context release];
    //[super dealloc];
}

@end
