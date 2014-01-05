//
//  IRenderingEngine.h
//  HelloArrow
//
//  Created by 林光海 on 13-12-26.
//  Copyright (c) 2013年 JackLinMaker. All rights reserved.
//

#ifndef HelloArrow_IRenderingEngine_h
#define HelloArrow_IRenderingEngine_h

// Physical orientation of a handheld device, equivalent to UIDeviceOrientation
enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

// Create an instance of the renderer and set up various OpenGL state.
struct IRenderingEngine* CreateRenderer1();
struct IRenderingEngine* CreateRenderer2();

// Interface to the OpenGL ES renderer; consumed by GLView.
struct IRenderingEngine {
    virtual void Initialize(int width, int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAnimation(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual ~IRenderingEngine() {}
};

#endif
