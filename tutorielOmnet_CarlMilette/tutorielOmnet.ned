//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package tutorielomnet_carlmilette;

import inet.LabsETS.StandardHostLab;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.ethernet.Eth10M;
import inet.nodes.ethernet.EtherSwitch;
import inet.nodes.inet.Router;


network TutorielOmnet
{
    parameters:
        int numStations = default(1);
        @display("bgb=455,319");
    submodules:
        station[numStations]: StandardHostLab {
            @display("p=74,229");
        }
        server: StandardHostLab {
            @display("p=389,50");
        }
        router: Router {
            @display("p=389,229");
        }
        etherSwitch: EtherSwitch {
            @display("p=228,224");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=135,81");
        }
    connections:
        for i=0..numStations -1 {
            station[i].ethg++ <--> Eth10M <--> etherSwitch.ethg++;
        }
        etherSwitch.ethg++ <--> Eth10M <--> router.ethg++;
        router.ethg++ <--> Eth10M <--> server.ethg++;
}
