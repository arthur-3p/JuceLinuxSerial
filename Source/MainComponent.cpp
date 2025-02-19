#include "MainComponent.h"

#if JUCE_WINDOWS
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if JUCE_LINUX
    #define SERIAL_PORT "/dev/ttyACM0"
#endif
#if defined JUCE_MAC
    #define SERIAL_PORT "/dev/tty.usbmodem101"
#endif

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    
    char openingErrorCode = openDevice();
    
    if (openingErrorCode != 1)
    {
        DBG("Failure opening device. Error: " << juce::String(openingErrorCode));
        return;
    }
    
    startTimer(100);
}

MainComponent::~MainComponent()
{
}

char MainComponent::openDevice()
{
    // Connection to serial port
    // If connection fails, return the error code otherwise
    return serial.openDevice(SERIAL_PORT, 9600);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

//==============================================================================
void MainComponent::timerCallback()
{
    // Create the string
    char buffer[15] = "hello\n";

//    // Write the string on the serial device
//    serial.writeString(buffer);
//    DBG(juce::String(buffer));

    // Read the string
    int readError = serial.readString(buffer, '\n', 20, 2000);
    if (readError > 0 )
        DBG(juce::String(buffer));
    else
        DBG("Error Reading. Error code: " << readError);
}
