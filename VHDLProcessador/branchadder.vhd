library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity branchadder is
    port (	data_i	 :	in 	unsigned (6 downto 0);
            branch_i :  in unsigned (6 downto 0);
			data_o	 :	out unsigned (6 downto 0)
		);
end entity;

architecture a_branchadder of branchadder is
	begin
		data_o <= data_i + branch_i;
end architecture;