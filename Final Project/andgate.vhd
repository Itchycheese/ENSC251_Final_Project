library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A : in std_logic;
	B : in std_logic;
            F : out std_logic_vector(2 downto 0));
end andGate;

architecture func of andGate is
begin
    then
   F <= A and B;
   end if
end func;
