library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( signal A : std_logic_vector(3 downto 0);
	signal B : std_logic_vector(3 downto 0);
            signal F : std_logic(3 downto 0)));
end andGate;

architecture func of andGate is
begin
   F <= A and B;
end func;
