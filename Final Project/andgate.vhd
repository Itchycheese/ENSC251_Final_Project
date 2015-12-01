library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A , C: in std_logic;
	B : in std_logic;
            F ,k: out std_logic_vector(4 downto 0));
end andGate;

architecture func of andGate is
begin
   F <= A and B;
C;
K;
end func;
