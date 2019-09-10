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

#include <tug_ros_diagnostic_msg_observer/ROSDiagnoisticMSGPlugin.h>
#include <tug_yaml/ProcessYaml.h>
#include <pluginlib/class_list_macros.h>
#include <set>
#include <string>

namespace tug_observer_plugins_cpp
{
ROSDiagnoisticMSGPlugin::ROSDiagnoisticMSGPlugin()
    : ObserverPluginBase("ros_diagnostic_msg")
{}

void ROSDiagnoisticMSGPlugin::initialize(XmlRpc::XmlRpcValue params)
{
    nodes_of_interrest_ = ProcessYaml::getValue<std::set<std::string> >("nodes_of_interest", params);

    ros_diagnstostics_sub_ = subscribe("/diagnostics", 1, &ROSDiagnoisticMSGPlugin::rosDiagnosticsCB, this);
}

void ROSDiagnoisticMSGPlugin::reset()
{}

void ROSDiagnoisticMSGPlugin::rosDiagnosticsCB(const diagnostic_msgs::DiagnosticArray &msg)
{
    for (size_t i = 0; i < msg.status.size(); ++i)
    {
        diagnostic_msgs::DiagnosticStatus tmp_status = msg.status[i];
        if ((tmp_status.level == diagnostic_msgs::DiagnosticStatus::ERROR) ||
            (tmp_status.level == diagnostic_msgs::DiagnosticStatus::STALE))
        {
            if (nodes_of_interrest_.count(tmp_status.name) > 0)
            {
                reportError(tmp_status.name,
                            "recieved_ros_diagnostic_msg_" + tmp_status.name,
                            "Received a diagnostiscs message from node " + tmp_status.name + ": '" + tmp_status.message
                                + "'",
                            tug_observers_msgs::observation::GENERAL_ERROR,
                            msg.header.stamp);
            }
        }
    }
}
}  // namespace tug_observer_plugins_cpp

PLUGINLIB_EXPORT_CLASS(tug_observer_plugins_cpp::ROSDiagnoisticMSGPlugin, tug_observers::ObserverPluginBase)
