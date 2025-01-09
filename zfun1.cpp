#include <gst/gst.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string pipeStr{};
    if(argc != 2) {
        cout << "Error:argc is " << argc << ", not equal to 2 !" << endl;
        return 0;
    } else {
        pipeStr = string("playbin uri=") + argv[1]; 
    }
    cout << "pipeStr = " << pipeStr << endl;
    while (1) {
        GstElement *pipeline;
        GstBus *bus;
        GstMessage *msg;
    
        /* Initialize GStreamer */
        gst_init (&argc, &argv);
    
        /* Build the pipeline */
        pipeline = gst_parse_launch (pipeStr.c_str(), NULL);
        /* Start playing */
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
    
        /* Wait until error or EOS */
        bus = gst_element_get_bus (pipeline);
        msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    
        /* Free resources */
        cout << "free resource start..." << flush <<  endl;
        gst_message_unref (msg);
        gst_object_unref (bus);
        gst_element_set_state (pipeline, GST_STATE_NULL);
        gst_object_unref (pipeline);
        cout << "free resource end." << flush << endl;
    }
    return 0;
}
