----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/12/2019 04:41:58 PM
-- Design Name: 
-- Module Name: WidthAdapter - Behavioral
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
use ieee.std_logic_1164.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use ieee.numeric_std.all;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

use work.parameters.all;

entity WidthAdapter is
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
end WidthAdapter;

architecture Behavioral of WidthAdapter is

	signal sCount : integer range 0 to cIWGlobal+cFWGlobal-1;
begin
--	O (OutIW+cFWGlobal-1 downto cFWGlobal-OutFW) <= I (OutIW+cFWGlobal-1 downto cFWGlobal-OutFW); --This is the desired part of the data based on the selected fixed width of this node
--	O (cIWGlobal+cFWGlobal-1 downto OutIW+cFWGlobal) <= (others => I (OutIW+cFWGlobal-1)); -- sign extension for the higher order integer bits
--	O (cFWGlobal-OutFW-1 downto 0) <= (others => '0'); --zero padding for the lower order fractional bits
   Gen1: for sCount in 0 to cIWGlobal+cFWGlobal-1 generate
		O (sCount) <= I (sCount) when ((sCount<OutIW+cFWGlobal) and (sCount>cFWGlobal-OutFW-1))  else
					I(OutIW+cFWGlobal-1) when sCount >= OutIW+cFWGlobal  else
					'0';
	end generate Gen1;
end Behavioral;
