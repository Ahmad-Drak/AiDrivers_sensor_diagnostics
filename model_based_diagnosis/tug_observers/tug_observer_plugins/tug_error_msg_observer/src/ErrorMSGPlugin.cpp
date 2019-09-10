/*
This file is part of the software provided by the tug ais group
Copyright (c) 2015, Clemens Muehlbacher
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <tug_error_msg_observer/ErrorMSGPlugin.h>
#include <tug_yaml/ProcessYaml.h>
#include <pluginlib/class_list_macros.h>
#include <tug_observers_msgs/observation.h>
#include <set>
#include <string>

namespace tug_observer_plugins_cpp
{
ErrorMSGPlugin::ErrorMSGPlugin()
    : ObserverPluginBase("error_msg")
{ }

void ErrorMSGPlugin::initialize(XmlRpc::XmlRpcValue params)
{
    nodes_of_interrest_ = ProcessYaml::getValue<std::set<std::string> >("nodes_of_interest", params);

    ros_out_sub_ = subscribe("/rosout", 1, &ErrorMSGPlugin::rosOutCB, this);
}

void ErrorMSGPlugin::reset()
{ }

void ErrorMSGPlugin::rosOutCB(const rosgraph_msgs::LogConstPtr &msg)
{
    if ((msg->level == rosgraph_msgs::Log::ERROR) || (msg->level == rosgraph_msgs::Log::FATAL))
    {
        if (nodes_of_interrest_.count(msg->name) > 0)
        {
            reportError(msg->name,
                        "recieved_error_msg_" + msg->name,
                        "Received a error message from node " + msg->name + ": '" + msg->msg + "'",
                        tug_observers_msgs::observation::GENERAL_ERROR,
                        msg->header.stamp);
        }
    }
}

}  // namespace tug_observer_plugins_cpp

PLUGINLIB_EXPORT_CLASS(tug_observer_plugins_cpp::ErrorMSGPlugin, tug_observers::ObserverPluginBase)