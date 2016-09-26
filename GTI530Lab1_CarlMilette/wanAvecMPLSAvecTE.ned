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

package gti530lab1_carlmilette;
import inet.LabsETS.DS0;
import inet.LabsETS.DS1;
import inet.LabsETS.EtherSwitchLan;
import inet.LabsETS.StandardHostLab;
import inet.LabsETS.fiberline;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.ethernet.Eth10M;
import inet.nodes.inet.Router;
import inet.nodes.mpls.RSVP_LSR;


//
// TODO documentation
//
network wanAvecMPLSavecTE
{
    @display("bgb=7500,4800;bgs=0.2,km");
    submodules:
        montrealServer: StandardHostLab {
            @display("p=4650,1175");
        }
        vancouverRouter: Router {
            @display("p=440,2175");
        }
        vancouverLAN: EtherSwitchLan {
            @display("p=440,2620");
        }
        calgaryLSR: RSVP_LSR {
            @display("p=1310,1895");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=340,260");
        }
        vancouverLSR: RSVP_LSR {
            @display("p=440,1395");
        }
        edmontonLSR: RSVP_LSR {
            @display("p=1725,820");
        }
        reginaLSR: RSVP_LSR {
            @display("p=2475,1490");
        }
        torontoLSR: RSVP_LSR {
            @display("p=4250,2390");
        }
        winnipegLSR: RSVP_LSR {
            @display("p=3165,1075");
        }
        montrealLSR: RSVP_LSR {
            @display("p=4595,1935");
        }
    connections:
        vancouverLSR.pppg++ <--> DS0 <--> calgaryLSR.pppg++;
        reginaLSR.pppg++ <--> DS0 <--> montrealLSR.pppg++;
        winnipegLSR.pppg++ <--> DS0 <--> montrealLSR.pppg++;
        vancouverLSR.pppg++ <--> DS1 <--> edmontonLSR.pppg++;
        calgaryLSR.pppg++ <--> DS1 <--> reginaLSR.pppg++;
        edmontonLSR.pppg++ <--> DS1 <--> reginaLSR.pppg++;
        edmontonLSR.pppg++ <--> DS1 <--> winnipegLSR.pppg++;
        torontoLSR.pppg++ <--> DS1 <--> montrealLSR.pppg++;
        calgaryLSR.pppg++ <--> fiberline <--> torontoLSR.pppg++;
        montrealLSR.pppg++ <--> Eth10M <--> montrealServer.pppg++;
        vancouverLSR.pppg++ <--> Eth10M <--> vancouverRouter.pppg++;
        vancouverLAN.switchInOut <--> Eth10M <--> vancouverRouter.ethg++;
}

