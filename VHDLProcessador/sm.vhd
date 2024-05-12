--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity sm is
	port(	rst	:	in std_logic;
			clk		:	in std_logic;
			state	:	out unsigned (2 downto 0)
		);
end entity;

architecture a_sm of sm is

	signal state_s : 	unsigned (2 downto 0);
	signal chg	   :	std_logic := '1';

	begin
		process (clk, rst)
		begin
			if rst = '1' then
				state_s <= "000";
--				chg <= '1';
			elsif rising_edge(clk) then
				if state_s = "011" then
					state_s <= "000";
				else
--				elsif chg = '1' then
					state_s <= state_s+1;
				end if;
			end if;

--			if rising_edge(clk) and chg = '0' then
--				chg <= '1';
--			elsif rising_edge(clk) then
--				chg <= '0';
--			end if;

		end process;
		state <= state_s;
end architecture;