# Countdown:
The countdown feature is a simple egg timer implementation that can allow our clock to count down from
a user set value. When the count reaches zero something will happen!

The countdown can be paused mid-flow or stopped. How we pause or stop it isn't decided yet and depends on the input interface.

## State diagram for countdown:
We can model all input responses as state changes in a state machine,

```mermaid
flowchart LR
   COUNTDOWN_INACTIVE -->
   COUNTDOWN_ACTIVE --> COUNTDOWN_DONE
   COUNTDOWN_PAUSED <--> COUNTDOWN_ACTIVE
   COUNTDOWN_PAUSED --> COUNTDOWN_INACTIVE
   COUNTDOWN_INACTIVE --> COUNTDOWN_EDIT
   COUNTDOWN_EDIT --> COUNTDOWN_INACTIVE
   COUNTDOWN_DONE --> COUNTDOWN_INACTIVE
```

And the edit responses in another state machine:

```mermaid
flowchart LR
EDIT_HOURS ->
EDIT_MINUTES -> 
EDIT_SECONDS ->
EDIT_INACTIVE ->
EDIT_HOURS
```
We can decide whether this edit state machine can be exited early (IE if EDIT_INACTIVE is connected to each other choice)
or if a user has to go through all states to arrive at EDIT_INACTIVE again and exit the edit mode.

The current progression when countdown is accessed for the first time is this:

At the moment, countdown inactive seems to be going to countdown paused when edit is pressed.
COUNTDOWN_INACTIVE
COUNTDOWN_PAUSED
COUNTDOWN_DONE
COUNTDOWN_INACTIVE
COUNTDOWN_INACTIVE

instead this should happen:

COUNTDOWN_INACTIVE
COUNTDOWN_EDIT
_add time here_
COUNTDOWN_INACTIVE (but with a non-zero time now)
then we need to press a different button
COUNTDOWN_ACTIVE (until timer reaches 00:00)
COUNTDOWN_DONE.

This is wrong! 
