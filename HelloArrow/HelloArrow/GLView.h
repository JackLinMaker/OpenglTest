//
//  GLView.h
//  HelloArrow
//
//  Created by 林光海 on 13-12-26.
//  Copyright (c) 2013年 JackLinMaker. All rights reserved.
//

#import "IRenderingEngine.hpp"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>


@interface GLView : UIView {
    EAGLContext* m_context;
    IRenderingEngine* m_renderingEngine;
    float m_timestamp;
}

-(void) drawView:(CADisplayLink *)displayLink;
-(void) didRotate:(NSNotification *)notification;

@end
