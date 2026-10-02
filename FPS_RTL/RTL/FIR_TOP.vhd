----------------------------------------------------------------------------------
-- Company: BTU
-- Engineer: Keyvan Shahin
-- 
-- Create Date: 09/14/2021 06:07:52 PM
-- Design Name: 
-- Module Name: FIR_TOP - Behavioral
-- Project Name: Fixed Point Conversion
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use ieee.numeric_std.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

use work.parameters.all;

entity FIR_TOP is
	--Generic(
	--	cIWGlobal		: integer := 32; --Input Integer part Width
	--	cFWGlobal		: integer := 32; --Input Fractional part Width
	--	cNumberOfTaps	: integer := 51
	--);
    Port ( 
			SampClk : in std_logic;
			Rst : in std_logic;
			iFIRin : in tDataPath;
			
			-- Width Inputs
			iMultIn1IW : in tIntWidthArray (cNumberOfTaps-1 downto 0);
			iMultIn2IW : in tIntWidthArray (cNumberOfTaps-1 downto 0);
			iMultIn1FW : in tFloatWidthArray (cNumberOfTaps-1 downto 0);
			iMultIn2FW : in tFloatWidthArray (cNumberOfTaps-1 downto 0);
			
			iAddIn1IW : in tIntWidthArray (cNumberOfTaps-1 downto 0);
			iAddIn2IW : in tIntWidthArray (cNumberOfTaps-1 downto 0);
			iAddIn1FW : in tFloatWidthArray (cNumberOfTaps-1 downto 0);
			iAddIn2FW : in tFloatWidthArray (cNumberOfTaps-1 downto 0);
			
			
			oFIRout : out tDataPath
		);
end FIR_TOP;

architecture Behavioral of FIR_TOP is
	-- importing components
	
	-- WC Adder/Subtractor
	component WC_AddSub is
		Generic(
		--	cIWGlobal		: integer := 32; --Input Integer part Width
		--	cFWGlobal		: integer := 32; --Input Fractional part Width
			cAddSubSel		: boolean := true --Add/Subtract Select
			);
		Port ( 
			I1 : in tDataPath;
			I2 : in tDataPath;
			O : out tDataPath;
	
			-- Widths for the Width Adapters
	
			In1IW	: in tIntWidth; --Output Integer part Width
			In1FW	: in tFloatWidth; --Output Fractional part Width
			In2IW	: in tIntWidth; --Output Integer part Width
			In2FW	: in tFloatWidth --Output Fractional part Width
	
			);
	end component WC_AddSub;

	-- WC Multiplier
	component WC_Mult is
		--Generic(
		--	cIWGlobal		: integer := 32; --Input Integer part Width
		--	cFWGlobal		: integer := 32 --Input Fractional part Width
		--	);
		Port ( 
			I1 : in tDataPath;
			I2 : in tDataPath;
			O : out tDataPath;
	
			-- Widths for the Width Adapters
	
			In1IW	: in tIntWidth; --Output Integer part Width
			In1FW	: in tFloatWidth; --Output Fractional part Width
			In2IW	: in tIntWidth; --Output Integer part Width
			In2FW	: in tFloatWidth --Output Fractional part Width
	
			);
	end component WC_Mult;

	-- signal definitions
	--type	tX	is array (cNumberOfTaps-1 downto 0) of tDataPath; --Delay Line Type
	signal	sX			: tDataPathArray (cNumberOfTaps-1 downto 0); -- Dealy Line
	signal	sMultOut	: tDataPathArray (cNumberOfTaps-1 downto 0); -- Multiplier Outputs
	signal	sMultOutWire: tDataPathArray (cNumberOfTaps-1 downto 0); -- Multiplier Outputs Wire
	signal	sAddIO		: tDataPathArray (cNumberOfTaps downto 0); -- Adder InOuts
	signal	sAddIOWire	: tDataPathArray (cNumberOfTaps downto 0); -- Adder InOuts
	
begin
	-- input output assignments
	sX(0) <= iFIRin;
	oFIRout <= sX(cNumberOfTaps-1);
	sAddIOWire (0) <= to_signed(0, cIWGlobal+cFWGlobal);
	
	-- FIR Delay line
	DelayLine:
	for i in 1 to cNumberOfTaps-1 generate
	begin
		process (SampClk,Rst)
			begin  
			if Rst = '0' then
				sX(i) <= to_signed(0, cIWGlobal+cFWGlobal); --Delay line init
			elsif (SampClk'event and SampClk = '1') then
				sX(i) <= sX(i-1);
			end if;
		end process;
	end generate;
	
	-- Multipliers
	MultGen:
	for i in 0 to cNumberOfTaps-1 generate
		process (Rst)
			begin  
			if Rst = '0' then
				sMultOut(i) <= to_signed(0, cIWGlobal+cFWGlobal); --Delay line init
			else
				sMultOut <= sMultOutWire;
			end if;
		end process;
		WC_MultX: WC_Mult 
		--Generic Map(
		--	cIWGlobal => cIWGlobal, --Input Integer part Width
		--	cFWGlobal => cFWGlobal  --Input Fractional part Width
		--	)
		Port Map( 
			I1 => sX(i),
			I2 => cCoeff(i),
			O => sMultOutWire(i),
	
			-- Widths for the Width Adapters
	
			In1IW => iMultIn1IW(i), --Output Integer part Width
			In1FW => iMultIn1FW(i), --Output Fractional part Width
			In2IW => iMultIn2IW(i), --Output Integer part Width
			In2FW => iMultIn2FW(i) --Output Fractional part Width
			);		
	end generate;
	
	-- Adders
	AddGen:
	for i in 0 to cNumberOfTaps-1 generate
		process (Rst)
			begin  
			if Rst = '0' then
				sAddIO(i) <= to_signed(0, cIWGlobal+cFWGlobal); --Delay line init
			else
				sAddIO <= sAddIOWire;
			end if;
		end process;
		WC_AddX: WC_AddSub 
		Generic Map(
		--	cIWGlobal => cIWGlobal, --Input Integer part Width
		--	cFWGlobal => cFWGlobal, --Input Fractional part Width
			cAddSubSel => true --Add/Subtract Select
			)
		Port Map( 
			I1 => sMultOut(i),
			I2 => sAddIO(i),
			O => sAddIOWire(i+1),
	
			-- Widths for the Width Adapters
	
			In1IW => iAddIn1IW(i), --Output Integer part Width
			In1FW => iAddIn1FW(i), --Output Fractional part Width
			In2IW => iAddIn2IW(i), --Output Integer part Width
			In2FW => iAddIn2FW(i) --Output Fractional part Width
			);	
	end generate;
	
end Behavioral;
