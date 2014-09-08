//
//  SWSoftKeyboardLayout.h
//  SWSoftKeyboard
//
//  Created by Spencer Williams on 9/4/14.
//  Copyright (c) 2014 Spencer Williams. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SWKeyDelegate;

/// An interface that describes how to interact with a keyboard layout
@interface SWSoftKeyboardLayout : NSObject
/// The delegate to pass to each of the keys
@property (nonatomic, weak) id<SWKeyDelegate> keyDelegate;
/**
 The keys of this layout.
 
 In this class this returns an empty array, but subclasses of this class should return filled arrays of SWSoftKeys.
 @param layoutState The state of the layout
 @return The keys in a particular state of this layout
 */
- (NSArray *)keysForState:(int)layoutState;
/**
 The number of possible states of this layout.
 
 Like `keys`, states should be defined in subclasses of this class.  
 Keyboards are initialized with a layout state of 0.  
 State descriptions may be handled internally to subclasses of this class.
 @return The number of possible states of thsi layout.
 */
- (int)layoutStates;

/**
 Returns an array of SWSoftKeyboardKeys based on an array of NSStrings.
 
 Assumes two layout states: 0=shift key unpressed (unstuck), 1=shift key pressed (stuck).  
 Key values will be identical to key labels.
 Key values and labels will not change between key sticky states.
 @param keyboardShiftUpCharacters   An array of characters corresponding to the "shift key up (unstuck)" layout state
 @param keyboardShiftDownCharacters An array of characters corresponding to the "shift key down (stuck)" layout state
 @return An array of SWSoftKeyboardKeys
 */
- (NSArray *)simpleKeysFromKeyboardShiftUpCharacters:(NSArray *)keyboardShiftUpCharacters
                         keyboardShiftDownCharacters:(NSArray *)keyboardShiftDownCharacters;
/**
 Returns common alphabet keys, in QWERTY order.
 
 @return Common alphabet keys in QWERTY order.
 */
- (NSArray *)commonAlphabetKeys;
/**
 Returns some basic control keys
 
 @param hasFn   Whether or not to include a fn ("function") key
 @param hasControl  Whether or not to include a "control" key
 @param hasAlt  Whether or not to include an "alt" key
 @param hasShift    Whether or not to include a "shift" key
 @param hasDone     Whether or not to include a "done" key
 @param hasBackspace    Whether or not to include a "delete" key
 @return An array of control keys.
 */
- (NSArray *)controlKeysWithFn:(BOOL)hasFn control:(BOOL)hasControl alt:(BOOL)hasAlt shift:(BOOL)hasShift command:(BOOL)hasCommand done:(BOOL)hasDone backspace:(BOOL)hasBackspace;
@end
