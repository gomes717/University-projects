--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--															--
--		Operações da ULA:									--
--															--
--		"00" - Adição										--
--															--
--		"01" - Subtração									--
--															--
--		"10" - Retorna o maior valor						--
--															--
--		"11" - Inverte o sinal da primeira entrada			--
--															--
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
	entity ULA is
		port( in_a 		:	in unsigned (15 downto 0);
			  in_b 		: 	in unsigned (15 downto 0);
			  sel 		: 	in unsigned (4 downto 0);
			  en 		:	in std_logic;
			  res 		:	out unsigned(15 downto 0);
			  zero 		: 	out std_logic;
			  greater 	: 	out std_logic;
			  neg 		: 	out std_logic;	
			  carry     :   out std_logic
			);
	end entity;

	architecture a_ULA of ULA is
		signal in_a_17, in_b_17, soma_17 : unsigned (16 downto 0);
	begin
		in_a_17 <= '0' & in_a;
		in_b_17 <= '0' & in_b;
		soma_17 <= in_a_17 + in_b_17;
		res <=  soma_17(15 downto 0) when sel = "00000" and en = '1' else
			    in_a - in_b when sel = "00001" and en = '1' else
			    in_a when in_a > in_b and sel ="00010" and en = '1' else
			    in_a when in_a = in_b and sel ="00110" and en = '1' else
				in_a when in_b > in_a and sel = "00010" and en = '1' else
				in_a when in_a < in_b and sel ="01000" and en = '1' else
				in_a when in_b < in_a and sel = "01000" and en = '1' else
				in_a when in_a = in_b and sel ="01000" and en = '1' else
				in_a when in_a = in_b and sel ="00010" and en = '1' else
			    --"0000000000000000"-in_a when sel = "00011" and en = '1' else
			    in_b when sel = "10000" and en = '1' else
			    (in_a * in_b) when sel = "00011" and en = '1' else
			    in_a / in_b when sel = "00100" and in_b /= "0000000000000000" and en = '1' else
			    in_b when sel = "11000" and en = '1' else
			    --in_a % in_b when sel = "00101" and en = '1' else
			   	"0000000000000000";
		zero <= '1' when in_a = in_b else
				'0';
		greater <= '1' when in_a > in_b else
				'0';
		neg <= in_a(15);
		
		carry <= soma_17(16) when sel = "00000" else
				 '1' when in_b > in_a and sel = "00001" else
				 '0';

	end architecture;