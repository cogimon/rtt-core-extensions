/* ============================================================
 *
 * This file is a part of RST-RT (CogIMon) project
 *
 * Copyright (C) 2016 by Dennis Leroy Wigand <dwigand at cor-lab dot uni-bielefeld dot de>
 *
 * This file may be licensed under the terms of the
 * GNU Lesser General Public License Version 3 (the ``LGPL''),
 * or (at your option) any later version.
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the LGPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the LGPL along with this
 * program. If not, go to http://www.gnu.org/licenses/lgpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The development of this software was supported by:
 *   European Community’s Horizon 2020 robotics program ICT-23-2014
 *     under grant agreement 644727 - CogIMon
 *   CoR-Lab, Research Institute for Cognition and Robotics
 *     Bielefeld University
 *
 * ============================================================ */
#ifndef KINEMATIC_CHAIN_JA_HPP
#define KINEMATIC_CHAIN_JA_HPP

#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>
#include <rtt/Component.hpp>
#include <rtt/os/Semaphore.hpp>

#include <Eigen/Dense>

#include <vector>

#include <Eigen/Core>
#include <time.h>
#include <rtt/os/TimeService.hpp>
#include <sstream>
#include <rtt/Logger.hpp>

#include <boost/shared_ptr.hpp>

#include <thread>
#include <memory>

// RST-RT includes
#include <rst-rt/kinematics/JointAngles.hpp>

#include "rtt-core-extensions/rtt-jointaware-taskcontext.hpp"

#include <port_container.hpp>

namespace cogimon {

class RTTKinematicChainJa: public RTTJointAwareTaskContext {
public:
	RTTKinematicChainJa(std::string const& name);
	virtual ~RTTKinematicChainJa() {
	}

	bool configureHook();
	void updateHook();

	// operation to configure the ports
	bool configureFBandCMDdimensions(int dimFB, int dimCmdInput);
	bool addPortRobotside(std::string portName, int dim);

	void retrieveJointMappingsHook(std::string const& port_name,
			std::map<std::string, int> const& mapping);

	void processJointMappingsHook();

	/**
	 * Provides the joint name to index mapping for other components to retrieve.
	 * If there isn't such an port (portName) existing, or used in an kinematic chain,
	 * the call will return an empty map. Otherwise it will contain the mapping.
	 */
	std::map<std::string, int> getJointMappingForPort(std::string portName);

protected:

private:
	int _feedback_dims;
	int _command_dims;
	std::vector<
			boost::shared_ptr<
					OutputPortContainer<rstrt::kinematics::JointAngles> > > _robot_chain_ports;
	// TODO change _feedback_port to normal OutputPort!
	OutputPortContainer<rstrt::kinematics::JointAngles> _feedback_port;

	InputPortContainer<rstrt::kinematics::JointAngles> _command_port;
	InputPortContainer<rstrt::kinematics::JointAngles> _robot_feedback_port;

	bool executeContinuously;

};

}
#endif
