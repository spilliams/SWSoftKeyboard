#9/9

##key delegates by key type

keyboard responds to content keys
who responds to control keys? well, let's list what control keys we have so far:

BACKSPACE: the keyboard should respond to this one, because it directly affects the content
DONE/NEXT: the keyboard should respond to this one, becuase the message should go back to the view controller (ie dismiss keyboard or update keyboard's layout from the VC's point of view)
SHIFT:
ALT:
CTRL:
FN: grouping all of the "meta" keys together because they each have the capacity to change the layout. But who changes the layout. Let's break it down case by case

IF LAYOUT RESPONDS TO META KEY

1. meta key is touched, so it goes from unstuck to stuck.
2. the meta key's delegate--a keyboard LAYOUT--is notified of the "sticking"
3. I honestly forget why I thought this case would be important

IF KEYBOARD RESPONDS TO META KEY

1. meta key is touched, so it goes from unstuck to stuck.
2. the meta key's delegate--a KEYBOARD--is notified of the "sticking"
3. The keyboard asks its layout for a new set of keys[1]. (This really only applies to control keys that change the layout, like switching from QWERTY to numpad). Note that this isn't a set of new keys, the 'Q' key is the same 'Q' key we had before (to avoid key-state-replication between layouts)
4. the keyboard asks each key to get into the right clothes for the keyboard state
5. keyboard redraws

Ok, so I've pretty much established that the keyboard responds to meta keys. That's good, it simplifies the delegate structure.

Next question: what if user hits Shift. Does other shift change label/value too?  
Answer: I think so. it would be under the part where keyboard asks its keys to get into the right clothes for keyboard state

[1] wait a minute. let's simplify by adding a layer.
proposal: add a third kind of key: LAYOUT KEY
(currently existing kinds: CONTENT and CONTROL)
actually we can leave this feature for later

##matrix, frames, key layout

since keyboard is a subclass of NSMatrix, the keys need to fit in a matrix layout  
this is a bit limiting, probably. Can we have matrix cells of different width? According to the [matrix programming guide](https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/Matrix/Concepts/AboutMatrices.html#//apple_ref/doc/uid/20000104-BCICHAAG)
"The only restriction is that all cell objects must be the same size." womp womp

So how do we do this then? the keyboard is a View and the keys are Buttons?

#9/4

attempting to organize my thoughts wrt keyboard
nbb seems to contain one, but it's completely unused
contacted the guy who wrote nbb, he might send me a sample
worst case: we implement our own subclass of nscontrol
take a cue from iphone's email keyboard

what are the pieces here?
- UCSoftKeyboard (NSControl?). listens for notifications regarding responder chain
        - has a type/layout (alphanumeric, email address, keypad, etc)
- UCSoftKeyboardKey (NSActionCell?). an individual key on the keyboard. kinda like a button
        - contains a default value ('b', '3', '+' etc)
        - contains a list of values for certain states
        - contains a default label (distinct but probably identical to default value)
        - contains a list of labels for certain states
        - can be sticky (press toggles it on or off, as opposed to momentary activation)
- UCStickyKeyDelegate (NSObject)

The SoftKeyboard is a StickyKeyDelegate, and has 2 modes (shift position)

typedef enum {
    UCSoftKeyTypeControl
    UCSoftKeyTypeContent
} UCSoftKeyType

examples of control: shift, return, delete
example layout:

@ . - _ +
1 2 3 4 5 6 7 8 9 0 ⌫
Q W E R T Y U I O P
 A S D F G H J K L ⏎
   Z X C V B N M
 ⌂ -----space---- ⌂
 
(after reading a lot on text stuff in the [Cocoa Event Handling Guide](https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/EventOverview/HandlingKeyEvents/HandlingKeyEvents.html) and the [Cocoa Text Architecture Guide](https://developer.apple.com/LIBRARY/mac/documentation/TextFonts/Conceptual/CocoaTextArchitecture/TextEditing/TextEditing.html#//apple_ref/doc/uid/TP40009459-CH3-SW1)
I don't need to fake real, system-level key events. In fact, if I do (and the keyboard contains ⌘) then the user can easily break out of the experience.
So we need to use a "fake" keyboard. One that can be given a text view to update. So, how do we start this?

1. UCHomeViewController owns a child UCSoftKeyboardViewController, and at least one NSTextField.
2. user taps a NSTextField
3. when NSTextField becomes first responder, it calls out to its delegate (NSControlTextEditingDelegate)
4. the delegate (which happens to be UCHomeViewController) displays the UCSoftKeyboardViewController, possibly scrolling the underlying view to keep the NSTextField in view.
5. user taps keys
6. Every key press is handled directly in UCSoftKeyboardViewController, which updates the UCSoftTextField value.
7. user presses enter/done: UCSoftKeyboardViewController calls out to its delegate (UCHomeViewController)
8. user taps outside text field: NSTextField relinquishes first responder, and calls out to its delegate
9. When delegate (UCHomeViewController) receives a message from either protocol, it dismisses the soft keyboard!