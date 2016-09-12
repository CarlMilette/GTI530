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
import inet.examples.httptools.socket.tenserverssocket.ethernetline;
import inet.LabsETS.EtherHostMod;
import ned.DatarateChannel;
import ned.DelayChannel;


//
// This Lan is composed of a number (numEtherSta) EtherHost2 stations connected to an ethernet switch.
//Stations will send data to each other locally.
//
module EtherLan
{
    parameters:
        int numEtherSta;// Number of stations in the lan 
        @display("bgb=1003,604;i=device/lan;bgg=50");

    submodules:
        etherSta[numEtherSta]: EtherHostMod {
            @display("p=248,79,ri,250,250");
        }
        switch: EtherSwitch {
            @display("p=479,302");
        }

    connections allowunconnected:
        for i=0..numEtherSta-1 {
            etherSta[i].ethg <--> DatarateChannel <--> switch.ethg++;

        }
}

