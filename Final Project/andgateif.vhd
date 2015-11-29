library ieee;
use ieee.std_logic_1164.all;

entity andGate is
   port( A : in std_logic;
	B : in std_logic;
            F : out std_logic);
end andGate;

architecture func of andGate is
begin
   if (A > B) then
   	F <= A and B;
   elsif (A < B) then
	F <= B;
   else
	F <= A;
   end if;
end func;
