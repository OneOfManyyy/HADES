----------------------------------------------------------------------------------
-- Company: BTU
-- Engineer: Keyvan Shahin
-- 
-- Create Date: 11/18/2019 04:40:07 PM
-- Design Name: 
-- Module Name: WC_Mult - Behavioral
-- Project Name: 
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

entity WC_Mult is
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
end WC_Mult;

architecture Behavioral of WC_Mult is
	-- importing components
	
	-- Width Adapter
	component WidthAdapter is
		--Generic(
		--	cIWGlobal		: integer := 32; --Input Integer part Width
		--	cFWGlobal		: integer := 32 --Input Fractional part Width
		--	);
		Port ( 
			--Input and Adapted Output
			I 		: in tDataPath;
			O 		: out tDataPath;
			--Configurable Output Widths
			OutIW	: in tIntWidth; --Output Integer part Width
			OutFW	: in tFloatWidth --Output Fractional part Width
			);
	end component WidthAdapter;
	
	-- Basic Multiplier
	component BasicMult is
	--Generic(
	--	cIWGlobal		: integer := 32; --Input Integer part Width
	--	cFWGlobal		: integer := 32 --Input Fractional part Width
	--	);
    Port ( 
		I1 : in tDataPath;
        I2 : in tDataPath;
        O : out signed (2*(cIWGlobal+cFWGlobal)-1 downto 0)
		);
	end component BasicAddSub;

	signal	sWAI1	: tDataPath; -- Width adapted Inputs
	signal	sWAI2	: tDataPath; -- Width adapted Inputs
	signal	sTempOut: signed (2*(cIWGlobal+cFWGlobal)-1 downto 0); -- Width adapted Inputs

begin
	WidthAdapter_inst1: WidthAdapter
	--Generic map
	--(
	--	cIWGlobal => cIWGlobal,
	--	cFWGlobal => cFWGlobal
	--)
	Port map
	(
		--Input and Adapted Output
		I => I1,
		O => sWAI1,
		--Configurable Output Widths
		OutIW => In1IW,
		OutFW => In1FW
	);
	
	WidthAdapter_inst2: WidthAdapter
	--Generic map
	--(
	--	cIWGlobal => cIWGlobal,
	--	cFWGlobal => cFWGlobal
	--)
	Port map
	(
		--Input and Adapted Output
		I => I2,
		O => sWAI2,
		--Configurable Output Widths
		OutIW => In2IW,
		OutFW => In2FW
	);

	BasicMult_inst1: BasicMult
	--Generic map
	--(
	--	cIWGlobal => cIWGlobal,
	--	cFWGlobal => cFWGlobal
	--)
    Port map
	( 
		I1 => sWAI1,
        I2 => sWAI2,
        O => sTempOut
	);
	
	--  -------------------------------------------------------------------------------------
	--  |                    |                    |                    |                    |
	--  |        IW          |        IW          |         FW         |         FW         |
	--  -------------------------------------------------------------------------------------
	O(cIWGlobal+cFWGlobal-1 downto 0) <= sTempOut(cIWGlobal+cFWGlobal+cFWGlobal-1 downto cFWGlobal);

end Behavioral;
