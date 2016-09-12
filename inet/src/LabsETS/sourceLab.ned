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

// Simple source that generates messages corresponding to sourceLabMsg.msg type at regular inter Arrival Time
// and send them thru the ouput.
// 
simple SourceLab
{
    parameters:
        int messageKind = default(0);
        volatile double interArrivalTime @unit(s)= default(0.1s);// time between generated messages
        volatile double delaiMax = default(intuniform(7,15)); // delaiMax value
//        volatile double tempsEcoule = default(intuniform(2,7)); // tempsEcoule value
        volatile double delaiEnvoi = default(intuniform(2,7)); // delai pour envoi des messages
        volatile int priorite = default(intuniform(1,3)); // tempsEcoule value
        bool colorGouvAffDom = default(false);
        volatile int gouvAffDom = default(intuniform(0,4));
        bool colorUrgent = default(false);
        bool delaiMessages = default(false);
        volatile double doubleUrgent = default(intuniform(0,1));
        @display("i=block/source");
        
    gates:
        output sortie;
}
