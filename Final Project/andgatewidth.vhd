library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A : in std_logic_vector(3 downto 0);
	B : in std_logic_vector(2 downto 0);
            F : out std_logic_vector(2 downto 0));
end andGate;

architecture func of andGate is
begin
   F <= A and B;
end func;
