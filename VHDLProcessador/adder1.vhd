--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity adder1 is
	port (	data_i	:	in 	unsigned (6 downto 0);
			data_o	:	out unsigned (6 downto 0)
		);
end entity;

architecture a_adder1 of adder1 is
	begin
		data_o <= data_i + 1;
end architecture;