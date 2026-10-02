----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/12/2019 04:41:58 PM
-- Design Name: 
-- Module Name: BasicAddSub - Behavioral
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

entity BasicAddSub is
	Generic(
		--cIWGlobal		: integer := 32; --Input Integer part Width
		--cFWGlobal		: integer := 32; --Input Fractional part Width
		cAddSubSel		: boolean := true   --true for add, false for sub
		);
    Port ( 
		I1 : in tDataPath;
        I2 : in tDataPath;
        O : out tDataPath
		);
end BasicAddSub;

architecture Behavioral of BasicAddSub is
begin
	O <= I1 + I2 when cAddSubSel else I1 - I2;
end Behavioral;
