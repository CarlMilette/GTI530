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

//
// TODO auto-generated module
//
simple SinkLab
{
    parameters:
        @display("i=block/sink");
        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
    // statistiques pour les nombres de paquets de chaque queue
        @statistic[queue1PktServed](source= count(paquetsQueue1); record=vector,stats; interpolationmode=none);
        @statistic[queue2PktServed](source=count(paquetsQueue2); record=vector,stats; interpolationmode=none);
        @statistic[queue3PktServed](source=count(paquetsQueue3); record=vector,stats; interpolationmode=none);
        @statistic[queue4PktServed](source=count(paquetsQueue4); record=vector,stats; interpolationmode=none);
        
            gates:
        input in[];
}
