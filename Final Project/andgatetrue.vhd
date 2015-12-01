library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A : in std_logic;
	B : in std_logic;
            F : out std_logic;
	C: in boolean);
end andGate;

architecture func of andGate is
begin
   F <= A and B;
   C <= True;
   C<= false;
end func;
