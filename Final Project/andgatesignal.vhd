library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( signal A : std_logic;
	signal B : std_logic;
            signal F : std_logic);
end andGate;

architecture func of andGate is
begin
   F <= A and B;
end func;
