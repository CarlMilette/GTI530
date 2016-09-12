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

package inet.LabsETS;
import inet.nodes.ethernet.EtherSwitch;
import inet.nodes.ethernet.Eth10M;
import inet.nodes.inet.StandardHost;


//
// This Lan is composed of a number (numStaSwitch) standardHost stations connected to an ethernet switch.
//The ethernet switch has an in-out gate that serves to connect the Lan to others devices outside the Lan.
//
module EtherSwitchLan
{
    parameters:
        int numStaSwitch;

        @display("bgb=1003,604;i=device/lan;bgg=50");

    gates:
        inout switchInOut;

    submodules:
        staSwitch[numStaSwitch]: StandardHostLab {
            @display("p=248,79,ri,250,250");
        }
        switchInLan: EtherSwitch {
            @display("p=479,302");
        }

    connections allowunconnected:

        switchInLan.ethg++ <--> switchInOut;

        for i=0..numStaSwitch-1 {
            switchInLan.ethg++ <--> Eth10M <--> staSwitch[i].ethg++;

        }
}

