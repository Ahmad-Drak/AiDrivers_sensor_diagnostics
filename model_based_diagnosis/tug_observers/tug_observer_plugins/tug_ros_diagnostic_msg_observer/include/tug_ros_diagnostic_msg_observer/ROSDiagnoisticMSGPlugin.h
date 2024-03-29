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

#ifndef TUG_ROS_DIAGNOSTIC_MSG_OBSERVER_ROSDIAGNOISTICMSGPLUGIN_H
#define TUG_ROS_DIAGNOSTIC_MSG_OBSERVER_ROSDIAGNOISTICMSGPLUGIN_H

#include <tug_observers/ObserverPluginBase.h>
#include <ros/ros.h>
#include <set>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <string>

namespace tug_observer_plugins_cpp
{
class ROSDiagnoisticMSGPlugin: public tug_observers::ObserverPluginBase
{
    std::set<std::string> nodes_of_interrest_;
    ros::Subscriber ros_diagnstostics_sub_;

public:
    ROSDiagnoisticMSGPlugin();
    virtual void initialize(XmlRpc::XmlRpcValue params);
    virtual void reset();
    void rosDiagnosticsCB(const diagnostic_msgs::DiagnosticArray &msg);
};
}  // namespace tug_observer_plugins_cpp

#endif  // TUG_ROS_DIAGNOSTIC_MSG_OBSERVER_ROSDIAGNOISTICMSGPLUGIN_H
