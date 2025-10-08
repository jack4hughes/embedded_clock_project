# Embdedded Clock/Timer Project:

I have an old bitmap screen lying around, which I have meant to do something with for ages. I have time between applying for jobs, so I might as well do it now! I want to implement the following functionality as an MVP but keep the project extendable and programmable. Eventually, I want more internet-connected features, like a weather screen or a notification bar. Maybe I could use embedded Alexa for this (but that would need a big upgrade).

At the moment, this code is fairly abstract. I haven't firmed any components apart from the screen, and I'm still deciding between using an ESP32 or a Pi Pico for this project.

You can find more documentation in the [docs](docs) folder.

## MVP functionality: 
To display the current time and switch to a timer setting when needed, the clock will need the following features:

- **Accurate timekeeping**: either through internet checking or an external timing chip designed for this functionality.
- **Multiple pages:** The user must be able to switch between clock, alarm, and timer modes. This means our view must have multiple "pages". The information displayed on the screen will change depending on which page we are on.
- **Easily Readable Text:** We will have to develop a way of storing characters or sprites for text. At the moment they are just stored as arrays within the code.
- **Intuitive UI:** The model will have to have intuitive ways of interacting with our clock, changing the alarm duration, timer time and other variables. This will be included in the physical design process.

# Hardware Structure:

At a hardware level, there are only 6 main components/subsystems:

- **Battery/Power supply:** This provides power to our system. Need to work out what voltage the screen will take.
- **Microcontroller:** this handles logic, inputs and outputs
- **User interface for the embedded system**: Physical controls that the end user can use to interact with the device.
- **Serial Port/Bluetooth connectivity:** We attach the screen to our computer.
- **LCD Dotmatrix screen:** This is what will display the time, 
- **Speaker/Buzzer:** for playing sounds.

## Inputs and Outputs:

Our controller has three inputs: 

- **Timing Chip**: This will be a more accurate timer than the built-in ESP32 clock
- **External Serial Input:** This will read incoming messages from a computer/another chip.
- **User Interface:** This will be how an end user interacts with the device, it could be buttons, knobs or some other form of input, but I'm keeping it abstract for now.

The system also has **three main outputs**:

- **LCD dot-matrix screen**: This will be our display.
- **Audio Out:** This could be a buzzer, a speaker or an analog VCA circuit. I havent decided yet. Probably a buzzer in the first implementation.
- **External Serial Output**: This is how we print error messages and information to send back to the computer. It is not used by the end-user.

```mermaid
---
title: Physical Components
---
flowchart

MicroController[Micro Controller]

subgraph External Inputs
Timer[Timing Chip]
UserInterface[User Interface]
Computer["External Computer 
Input"]
end

SerialInterface("Serial 
Interface")
Battery[Power]

subgraph Outputs
DotMatrixScreen[LCD Dot-matrix]
AudioOut
end 

Timer -- controls timing of ---> MicroController
SerialInterface <-- Serial Comms --> MicroController
UserInterface -- commands ---> MicroController
MicroController -- Drives --> DotMatrixScreen
Battery -- powers --> MicroController
Battery -- powers --> DotMatrixScreen
Computer <-- serial comms--> SerialInterface
MicroController -- Plays sounds through --> AudioOut

```

# Software Design

The software on the microcontroller is designed to be modular. Different functions are seperated out into pages, and pages are designed to interface with the rest of the software as little as possible. For example, a simple clock might have four pages:

- **Alarm:** This sets and processes the alarm logic.
- **Timer:** A timer that counts up from the start.
- **Clock:** A standard clock screen.

All these pages need to react differently to button presses, and send different info out to the screen, but we only need to send one thing out: The current display information. We only need button presses and timer information to come in.

```mermaid
---
title: Software Components
---
flowchart TD
ScreenDriver[Screen Driver]

subgraph view
  ViewModelInterface[view model interface]
  ScreenDriver
  BitmapLogic[Bitmap Update Logic]
  Speaker[Speaker/buzzer]
  UART[UART module]
  ViewModelInterface --> BitmapLogic
  BitmapLogic -- updates bitmap --> ScreenDriver
	ViewModelInterface--> Speaker
	ViewModelInterface--> UART
end

subgraph model
timer

timer --> ClockUpdater
timer --> TimerUpdater
timer --> AlarmUpdater

subgraph Clock
ClockInfo[clock Info]
ClockUpdater
ClockViewUpdater
end

subgraph Timer
TimerInfo[timer Info]
TimerUpdater
TimerViewUpdater
end

subgraph Alarm
AlarmInfo[alarm Info]
AlarmUpdater
AlarmViewUpdater
end

modelViewInterface["High-Level Model
Communication"]

ClockUpdater --> ClockInfo
TimerUpdater --> TimerInfo
AlarmUpdater --> AlarmInfo

ClockInfo --> ClockViewUpdater --> modelViewInterface
TimerInfo --> TimerViewUpdater --> modelViewInterface
AlarmInfo --> AlarmViewUpdater --> modelViewInterface
end

subgraph controller
ControlInput
ControlPreProcessing[process inputs]
CurrentStateMachine[Control State Machine]

ControlInput --> ControlPreProcessing
ControlPreProcessing --> CurrentStateMachine
end

CurrentStateMachine -- changes current page --> ViewModelInterface
CurrentStateMachine -- commands --> ClockUpdater
CurrentStateMachine -- commands --> TimerUpdater
CurrentStateMachine -- commands --> AlarmUpdater
modelViewInterface -- sends updates to --> ViewModelInterface
```
