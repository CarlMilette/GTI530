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

import ned.DatarateChannel;

//Firmin Mah, april 2015
// Digital signals links to use in some connexions



// 64 kilobit/sec. 
// Delay 20 ms typique
//
channel DS0 extends DatarateChannel
{
    datarate = 64kbps;
    delay = 20ms;
}

//
// 1.544 megabit/sec. 
// Delay 10 ms typique
//
channel DS1 extends DatarateChannel
{
    datarate = 1.544Mbps;
    delay = 10ms;
}

//
// 44.736 megabit/sec. 
// Delay 40 ms typique
//
channel DS3 extends DatarateChannel
{
    datarate = 44.736Mbps;
    delay = 40ms;
}


//
// fiberline 512 megabit/sec. 
// Delay 100 us typique
//
channel fiberline extends ned.DatarateChannel
{
    parameters:
        delay = 100us;
        datarate = 512Mbps;
}