library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A : in std_logic;
	B : in STD_logic;
            F : OUT std_logic);
end andGate;

architecture func of andGate is
begin
   F <= a and B;
end func;
