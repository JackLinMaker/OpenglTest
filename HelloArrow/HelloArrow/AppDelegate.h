//
//  AppDelegate.h
//  HelloArrow
//
//  Created by 林光海 on 14-1-4.
//  Copyright (c) 2014年 JackLinMaker. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UIWindow* m_window;
    GLView* m_view;
}

@property (strong, nonatomic) UIWindow *m_window;

@end
