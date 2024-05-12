library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity processador is
	port (	rst		:	in  std_logic;
			clk		:	in 	std_logic;
			state	:	out unsigned (2 downto 0);	
			PC_o	:	out unsigned (6 downto 0);
			opcode	:	out unsigned (14 downto 0);
			reg1_o	:	out unsigned (15 downto 0);
			reg2_o	:	out unsigned (15 downto 0);	
			ula_o	:	out unsigned (15 downto 0);
			ram_o_top	:	out unsigned (15 downto 0)
		);
end entity;

architecture a_processador of processador is
	component pc is
		port(	clk	  	:	in std_logic;
		 		rst     : in std_logic;
		 		wr_en	:	in std_logic;
		 		data_i  :	in unsigned (6 downto 0);
		 		data_o  : 	out unsigned (6 downto 0)
			);
	end component;

	component adder1 is
		port (	data_i	:	in 	unsigned (6 downto 0);
				data_o	:	out unsigned (6 downto 0)
		);
	end component;

	component rom is
		port(	clk		:	in std_logic;
				address :	in unsigned(6 downto 0);
				data	:	out unsigned(14 downto 0)
		);
	end component;

	component reg is
		port(	clk	  		:	in std_logic;
		 		rst 	  	:	in std_logic;
		 		wr_en	  	:	in std_logic;
		 		data_in  	:	in unsigned  (14 downto 0);
				data_out	:	out unsigned (14 downto 0);
				cte 		:	out unsigned (7 downto 0);
		 		add_jmp		:	out unsigned (6 downto 0);
				ALUop		:	out unsigned (4 downto 0);
				instr		:	out unsigned (3 downto 0);
		 		read_reg_a	:	out unsigned (2 downto 0);
				read_reg_b	:	out unsigned (2 downto 0);
				BranchOp    :   out unsigned (3 downto 0);
		 		state 		:	in unsigned  (2 downto 0);
				flagEn		:	out std_logic;
				REGscr		:	out std_logic;
				ram_add		:	out unsigned (6 downto 0);
		 		RAMread		:	out std_logic
		);
	end component;

	component sm is
		port(	rst	:	in std_logic;
				clk		:	in std_logic;
				state	:	out unsigned (2 downto 0)
		);
	end component;

	component uc is port (	clk			:	in std_logic;
							state 		:	in unsigned (2 downto 0);
							instr		:	in unsigned (3 downto 0);
							flag_i      :   in unsigned (1 downto 0);
							rst			:	in std_logic;
							zero		:	in std_logic;
							carry		:	in std_logic;
							jump_en 	:	out std_logic;
							PCWrite		:	out std_logic;
							IRWrite		:	out std_logic;
							ALUen		:	out std_logic;
							ALUScrB		:	out std_logic;
							PCScr		:	out unsigned (1 downto 0);
							RegWrite	:   out std_logic;
							BranchEn    :   out std_logic;
							RAMen		:	out std_logic;
							branchop    :   in unsigned (3 downto 0);
							RAMsrc		:	out std_logic
		);
	end component;

	component banco_regs is
		port (	read_reg_a	:	in unsigned (2 downto 0);
				read_reg_b	:	in unsigned (2 downto 0);
				write_reg	:	in unsigned (2 downto 0);
				write_data	:	in unsigned (15 downto 0);
				wr_en		:	in std_logic;	
				clk			:	in std_logic;
				rst			:	in std_logic;
				read_data_a :	out unsigned (15 downto 0);
				read_data_b :	out unsigned (15 downto 0)
		);
	end component;

	component ULA is
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
	end component;

	component branchadder is
		port (	data_i	 :	in 	unsigned (6 downto 0);
				branch_i :  in  unsigned (6 downto 0);
				data_o   :	out unsigned (6 downto 0)
		);
	end component;

	component reg1bit is
		port(clk	  :	in std_logic;
		 rst 	  :	in std_logic;
		 wr_en	  :	in std_logic;
		 data_in  :	in std_logic;
		 data_out : out std_logic
		);
	end component;

	component ram is
		port (
            clk         :   in std_logic;
            address     :   in unsigned (6 downto 0);
            wr_en       :   in std_logic;
            data_in     :   in unsigned (15 downto 0);
            data_out    :   out unsigned (15 downto 0)
		);
	end component;
	


	signal read_data_a, read_data_b 	:	unsigned (15 downto 0);
	signal ula_s						:	unsigned (15 downto 0);
	signal data_a, data_b 				:	unsigned (15 downto 0);
	signal ctex							:	unsigned (15 downto 0);
	signal add_ex						:	unsigned (15 downto 0);
	signal opcode_s1, opcode_s2			:	unsigned (14 downto 0);
	signal cte							:	unsigned (7 downto 0);
	signal add_jmp, pc_add				:	unsigned (6 downto 0);
	signal add_s1, add_s2 				:	unsigned (6 downto 0);
	signal ALUop						:	unsigned (4 downto 0);
	signal instr						:	unsigned (3 downto 0);
	signal read_reg_a, read_reg_b 		:	unsigned (2 downto 0);
	signal state_s						:	unsigned (2 downto 0);
	signal PCScr						:	unsigned (1 downto 0);
	signal PCWrite, IRWrite, RegWrite	:	std_logic;
	signal ALUen, ALUScrB       		:	std_logic;
	signal MVen							:	std_logic;
	signal branch_en                    :	std_logic;
	signal branch_s                     :	unsigned (6 downto 0);
	signal add_s3	                    :	unsigned (6 downto 0);  --saida do branch
	signal zero,greater                 :   std_logic;
	signal flag_s						:   unsigned (1 downto 0);
	signal condition_code				:   unsigned (3 downto 0);
	signal zero_s, flagEn, carry_s		:	std_logic;
	signal ram_i, ram_add				:	unsigned (6 downto 0);
	signal RAMen, REGscr, RAMsrc		:	std_logic;
	signal regs_wr, ram_o				:	unsigned (15 downto 0);
	signal RAMread						:	std_logic;
	
	begin

		pcu			:	pc port map (clk => clk, rst => rst, wr_en => PCWrite, data_i => pc_add, data_o => add_s1);

		adder		:	adder1 port map (data_i => add_s1, data_o => add_s2);

		romu		:	rom port map (clk => clk, address => add_s1, data => opcode_s1);

		instr_reg 	:	reg port map (clk => clk, rst => rst, wr_en => '1', data_in => opcode_s1, data_out => opcode_s2,
									  read_reg_a => read_reg_a, read_reg_b => read_reg_b, cte => cte, ALUop => ALUop,
									  instr => instr, add_jmp => add_jmp,BranchOp => condition_code, ram_add => ram_add,
									  regSCR => regSCR, flagEn => flagEn, state => state_s, RAMread => RAMread);

		statem		:	sm port map (clk => clk, rst => rst, state => state_s);

		ucu			:	uc port map (clk => clk, instr => instr, state => state_s, PCWrite => PCWrite, RegWrite => RegWrite,
									 IRWrite => IRWrite, ALUen => ALUen, ALUScrB => ALUScrB, PCScr => PCScr, BranchEn => branch_en,
									 rst => rst, flag_i => flag_s, branchop => condition_code,
									 zero => zero_s, carry => carry_s, RAMen => RAMen, RAMsrc => RAMsrc);

		regs		:	banco_regs port map (read_reg_a => read_reg_a, read_reg_b => read_reg_b, write_reg => read_reg_a,
						   				     wr_en => RegWrite, clk => clk, rst => rst,read_data_a => read_data_a,
									   		 read_data_b => read_data_b, write_data => regs_wr);

		alu			:	ULA port map (in_a => data_a, in_b => data_b, en => ALUen, sel => ALUop, res => ula_s,zero => zero,greater => greater);

		b_adder     :   branchadder port map (data_i => add_s2, branch_i => branch_s, data_o => add_s3);

		zero_reg	:	reg1bit	port map (clk => clk, rst => rst, wr_en => flagEn, data_in => zero, data_out => zero_s);

		carry_reg	:	reg1bit port map (clk => clk, rst => rst, wr_en => flagEn, data_in => greater, data_out => carry_s);

		ramu		:	ram port map (clk => clk, address => ram_i, wr_en => RAMen, data_in => ula_s, data_out => ram_o);

		PC_o <= add_s1;	

		opcode <= opcode_s2;

		state <= state_s;

		reg1_o <= read_data_a;
		reg2_o <= read_data_b;

		data_a <= read_data_a; 
		data_b <= read_data_b when ALUScrB = '0' else
				  ctex;

		branch_s <= add_jmp when branch_en = '1' else 
					"0000000";


		pc_add <= add_jmp when PCScr = "01" else 
				  add_s3 when PCScr = "10" else
				  add_s2;

		ctex <= cte(7) & cte(7) & cte(7) & cte(7) &
				cte(7) & cte(7) & cte(7) & cte(7) &
				cte(7 downto 0);

		regs_wr <= ram_o when REGscr = '1' else
				   ula_s;

		add_ex <= "000000000" & add_s1;

		ula_o <= ula_s;

		ram_i <= data_a(6 downto 0) when RAMsrc = '1' else
				 ram_add;

		ram_o_top <= ram_o when RAMread = '1' else
					 "1111111111111111";

end architecture;