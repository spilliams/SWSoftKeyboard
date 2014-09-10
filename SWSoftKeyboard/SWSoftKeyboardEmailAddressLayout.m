//
//  SWSoftKeyboardEmailAddressLayout.m
//  SWSoftKeyboard
//
//  Created by Spencer Williams on 9/4/14.
//  This is free and unencumbered software released into the public domain.
//

#import "SWSoftKeyboardEmailAddressLayout.h"
#import "SWSoftKeyboardLayoutHelper.h"

@interface SWSoftKeyboardEmailAddressLayout ()
@property (nonatomic, strong) NSMutableDictionary *keysForStates;
@end

@implementation SWSoftKeyboardEmailAddressLayout
@synthesize keyDelegate;

- (instancetype)init
{
    if (self = [super init]) {
        self.keysForStates = [NSMutableDictionary new];
    }
    return self;
}
- (NSArray *)keysForState:(int)layoutState
{
    NSArray *keys = [self.keysForStates objectForKey:[NSNumber numberWithInt:layoutState]];
    if (keys != nil) {
        return keys;
    }
    
    // this layout actually doesn't care about layout state
    
    NSMutableArray *keysArray = [NSMutableArray new];
    
    NSArray *alphabetKeys = [SWSoftKeyboardLayoutHelper commonAlphabetKeys];
    NSArray *numberKeys = [SWSoftKeyboardLayoutHelper simpleKeysFromKeyboardShiftUpCharacters:@[@"1",@"2",@"3",@"4",@"5",@"6",@"7",@"8",@"9",@"0"]
                                                                  keyboardShiftDownCharacters:@[@"1",@"2",@"3",@"4",@"5",@"6",@"7",@"8",@"9",@"0"]];
    NSArray *punctuationLetters = @[@"@",@"-",@"_",@".",@"+"];
    NSArray *punctuationKeys = [SWSoftKeyboardLayoutHelper simpleKeysFromKeyboardShiftUpCharacters:punctuationLetters
                                                                       keyboardShiftDownCharacters:punctuationLetters];
    
    // TODO: update frame data for all keys
    
    [keysArray addObjectsFromArray:alphabetKeys];
    [keysArray addObjectsFromArray:numberKeys];
    [keysArray addObjectsFromArray:punctuationKeys];
    
    [self.keysForStates setObject:keysArray forKey:[NSNumber numberWithInt:layoutState]];
    
    return keysArray;
}
- (NSRect)keyboardFrameForState:(int)layoutState
{
    // TODO: unimplemented
    return NSMakeRect(0, 0, 500, 500);
}
- (int)layoutStates
{
    return 2; // shift up, shift down
}
@end
