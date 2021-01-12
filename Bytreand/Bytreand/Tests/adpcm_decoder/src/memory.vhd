--
-- Copyright (c) 2010 Ricardo Menotti, All Rights Reserved.
--
-- Permission to use, copy, modify, and distribute this software and its
-- documentation for NON-COMERCIAL purposes and without fee is hereby granted 
-- provided that this copyright notice appears in all copies.
--
-- RICARDO MENOTTI MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
-- OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
-- IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
-- NON-INFRINGEMENT. RICARDO MENOTTI SHALL NOT BE LIABLE FOR ANY DAMAGES
-- SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS
-- SOFTWARE OR ITS DERIVATIVES.
--
-- Generated at Tue May 28 15:32:42 BRT 2013
--

-- IEEE Libraries --
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity block_ram_indata is
generic(
	data_width : integer := 8;
	address_width : integer := 8
);
port(
	data_in : in std_logic_vector(data_width-1 downto 0) := (others => '0');
	address : in std_logic_vector(address_width-1 downto 0);
	we: in std_logic := '0';
	oe: in std_logic := '1';
	clk : in std_logic;
	data_out : out std_logic_vector(data_width-1 downto 0));
end block_ram_indata;

architecture rtl of block_ram_indata is

constant mem_depth : integer := 2**address_width;
type ram_type is array (mem_depth-1 downto 0)
of std_logic_vector (data_width-1 downto 0);

signal read_a : std_logic_vector(address_width-1 downto 0);
signal RAM : ram_type := ram_type'(
	 ("00000000000000000000000000100101"),	 -- 511	37
	 ("00000000000000000000000000011011"),	 -- 510	27
	 ("00000000000000000000000000010001"),	 -- 509	17
	 ("00000000000000000000000000000111"),	 -- 508	7
	 ("00000000000000000000000001111100"),	 -- 507	124
	 ("00000000000000000000000001110010"),	 -- 506	114
	 ("00000000000000000000000001101000"),	 -- 505	104
	 ("00000000000000000000000001011110"),	 -- 504	94
	 ("00000000000000000000000001010100"),	 -- 503	84
	 ("00000000000000000000000001001010"),	 -- 502	74
	 ("00000000000000000000000001000000"),	 -- 501	64
	 ("00000000000000000000000000110110"),	 -- 500	54
	 ("00000000000000000000000000101100"),	 -- 499	44
	 ("00000000000000000000000000100010"),	 -- 498	34
	 ("00000000000000000000000000011000"),	 -- 497	24
	 ("00000000000000000000000000001110"),	 -- 496	14
	 ("00000000000000000000000000000100"),	 -- 495	4
	 ("00000000000000000000000001111001"),	 -- 494	121
	 ("00000000000000000000000001101111"),	 -- 493	111
	 ("00000000000000000000000001100101"),	 -- 492	101
	 ("00000000000000000000000001011011"),	 -- 491	91
	 ("00000000000000000000000001010001"),	 -- 490	81
	 ("00000000000000000000000001000111"),	 -- 489	71
	 ("00000000000000000000000000111101"),	 -- 488	61
	 ("00000000000000000000000000110011"),	 -- 487	51
	 ("00000000000000000000000000101001"),	 -- 486	41
	 ("00000000000000000000000000011111"),	 -- 485	31
	 ("00000000000000000000000000010101"),	 -- 484	21
	 ("00000000000000000000000000001011"),	 -- 483	11
	 ("00000000000000000000000000000001"),	 -- 482	1
	 ("00000000000000000000000001110110"),	 -- 481	118
	 ("00000000000000000000000001101100"),	 -- 480	108
	 ("00000000000000000000000001100010"),	 -- 479	98
	 ("00000000000000000000000001011000"),	 -- 478	88
	 ("00000000000000000000000001001110"),	 -- 477	78
	 ("00000000000000000000000001000100"),	 -- 476	68
	 ("00000000000000000000000000111010"),	 -- 475	58
	 ("00000000000000000000000000110000"),	 -- 474	48
	 ("00000000000000000000000000100110"),	 -- 473	38
	 ("00000000000000000000000000011100"),	 -- 472	28
	 ("00000000000000000000000000010010"),	 -- 471	18
	 ("00000000000000000000000000001000"),	 -- 470	8
	 ("00000000000000000000000001111101"),	 -- 469	125
	 ("00000000000000000000000001110011"),	 -- 468	115
	 ("00000000000000000000000001101001"),	 -- 467	105
	 ("00000000000000000000000001011111"),	 -- 466	95
	 ("00000000000000000000000001010101"),	 -- 465	85
	 ("00000000000000000000000001001011"),	 -- 464	75
	 ("00000000000000000000000001000001"),	 -- 463	65
	 ("00000000000000000000000000110111"),	 -- 462	55
	 ("00000000000000000000000000101101"),	 -- 461	45
	 ("00000000000000000000000000100011"),	 -- 460	35
	 ("00000000000000000000000000011001"),	 -- 459	25
	 ("00000000000000000000000000001111"),	 -- 458	15
	 ("00000000000000000000000000000101"),	 -- 457	5
	 ("00000000000000000000000001111010"),	 -- 456	122
	 ("00000000000000000000000001110000"),	 -- 455	112
	 ("00000000000000000000000001100110"),	 -- 454	102
	 ("00000000000000000000000001011100"),	 -- 453	92
	 ("00000000000000000000000001010010"),	 -- 452	82
	 ("00000000000000000000000001001000"),	 -- 451	72
	 ("00000000000000000000000000111110"),	 -- 450	62
	 ("00000000000000000000000000110100"),	 -- 449	52
	 ("00000000000000000000000000101010"),	 -- 448	42
	 ("00000000000000000000000000100000"),	 -- 447	32
	 ("00000000000000000000000000010110"),	 -- 446	22
	 ("00000000000000000000000000001100"),	 -- 445	12
	 ("00000000000000000000000000000010"),	 -- 444	2
	 ("00000000000000000000000001110111"),	 -- 443	119
	 ("00000000000000000000000001101101"),	 -- 442	109
	 ("00000000000000000000000001100011"),	 -- 441	99
	 ("00000000000000000000000001011001"),	 -- 440	89
	 ("00000000000000000000000001001111"),	 -- 439	79
	 ("00000000000000000000000001000101"),	 -- 438	69
	 ("00000000000000000000000000111011"),	 -- 437	59
	 ("00000000000000000000000000110001"),	 -- 436	49
	 ("00000000000000000000000000100111"),	 -- 435	39
	 ("00000000000000000000000000011101"),	 -- 434	29
	 ("00000000000000000000000000010011"),	 -- 433	19
	 ("00000000000000000000000000001001"),	 -- 432	9
	 ("00000000000000000000000001111110"),	 -- 431	126
	 ("00000000000000000000000001110100"),	 -- 430	116
	 ("00000000000000000000000001101010"),	 -- 429	106
	 ("00000000000000000000000001100000"),	 -- 428	96
	 ("00000000000000000000000001010110"),	 -- 427	86
	 ("00000000000000000000000001001100"),	 -- 426	76
	 ("00000000000000000000000001000010"),	 -- 425	66
	 ("00000000000000000000000000111000"),	 -- 424	56
	 ("00000000000000000000000000101110"),	 -- 423	46
	 ("00000000000000000000000000100100"),	 -- 422	36
	 ("00000000000000000000000000011010"),	 -- 421	26
	 ("00000000000000000000000000010000"),	 -- 420	16
	 ("00000000000000000000000000000110"),	 -- 419	6
	 ("00000000000000000000000001111011"),	 -- 418	123
	 ("00000000000000000000000001110001"),	 -- 417	113
	 ("00000000000000000000000001100111"),	 -- 416	103
	 ("00000000000000000000000001011101"),	 -- 415	93
	 ("00000000000000000000000001010011"),	 -- 414	83
	 ("00000000000000000000000001001001"),	 -- 413	73
	 ("00000000000000000000000000111111"),	 -- 412	63
	 ("00000000000000000000000000110101"),	 -- 411	53
	 ("00000000000000000000000000101011"),	 -- 410	43
	 ("00000000000000000000000000100001"),	 -- 409	33
	 ("00000000000000000000000000010111"),	 -- 408	23
	 ("00000000000000000000000000001101"),	 -- 407	13
	 ("00000000000000000000000000000011"),	 -- 406	3
	 ("00000000000000000000000001111000"),	 -- 405	120
	 ("00000000000000000000000001101110"),	 -- 404	110
	 ("00000000000000000000000001100100"),	 -- 403	100
	 ("00000000000000000000000001011010"),	 -- 402	90
	 ("00000000000000000000000001010000"),	 -- 401	80
	 ("00000000000000000000000001000110"),	 -- 400	70
	 ("00000000000000000000000000111100"),	 -- 399	60
	 ("00000000000000000000000000110010"),	 -- 398	50
	 ("00000000000000000000000000101000"),	 -- 397	40
	 ("00000000000000000000000000011110"),	 -- 396	30
	 ("00000000000000000000000000010100"),	 -- 395	20
	 ("00000000000000000000000000001010"),	 -- 394	10
	 ("00000000000000000000000000000000"),	 -- 393	0
	 ("00000000000000000000000001110101"),	 -- 392	117
	 ("00000000000000000000000001101011"),	 -- 391	107
	 ("00000000000000000000000001100001"),	 -- 390	97
	 ("00000000000000000000000001010111"),	 -- 389	87
	 ("00000000000000000000000001001101"),	 -- 388	77
	 ("00000000000000000000000001000011"),	 -- 387	67
	 ("00000000000000000000000000111001"),	 -- 386	57
	 ("00000000000000000000000000101111"),	 -- 385	47
	 ("00000000000000000000000000100101"),	 -- 384	37
	 ("00000000000000000000000000011011"),	 -- 383	27
	 ("00000000000000000000000000010001"),	 -- 382	17
	 ("00000000000000000000000000000111"),	 -- 381	7
	 ("00000000000000000000000001111100"),	 -- 380	124
	 ("00000000000000000000000001110010"),	 -- 379	114
	 ("00000000000000000000000001101000"),	 -- 378	104
	 ("00000000000000000000000001011110"),	 -- 377	94
	 ("00000000000000000000000001010100"),	 -- 376	84
	 ("00000000000000000000000001001010"),	 -- 375	74
	 ("00000000000000000000000001000000"),	 -- 374	64
	 ("00000000000000000000000000110110"),	 -- 373	54
	 ("00000000000000000000000000101100"),	 -- 372	44
	 ("00000000000000000000000000100010"),	 -- 371	34
	 ("00000000000000000000000000011000"),	 -- 370	24
	 ("00000000000000000000000000001110"),	 -- 369	14
	 ("00000000000000000000000000000100"),	 -- 368	4
	 ("00000000000000000000000001111001"),	 -- 367	121
	 ("00000000000000000000000001101111"),	 -- 366	111
	 ("00000000000000000000000001100101"),	 -- 365	101
	 ("00000000000000000000000001011011"),	 -- 364	91
	 ("00000000000000000000000001010001"),	 -- 363	81
	 ("00000000000000000000000001000111"),	 -- 362	71
	 ("00000000000000000000000000111101"),	 -- 361	61
	 ("00000000000000000000000000110011"),	 -- 360	51
	 ("00000000000000000000000000101001"),	 -- 359	41
	 ("00000000000000000000000000011111"),	 -- 358	31
	 ("00000000000000000000000000010101"),	 -- 357	21
	 ("00000000000000000000000000001011"),	 -- 356	11
	 ("00000000000000000000000000000001"),	 -- 355	1
	 ("00000000000000000000000001110110"),	 -- 354	118
	 ("00000000000000000000000001101100"),	 -- 353	108
	 ("00000000000000000000000001100010"),	 -- 352	98
	 ("00000000000000000000000001011000"),	 -- 351	88
	 ("00000000000000000000000001001110"),	 -- 350	78
	 ("00000000000000000000000001000100"),	 -- 349	68
	 ("00000000000000000000000000111010"),	 -- 348	58
	 ("00000000000000000000000000110000"),	 -- 347	48
	 ("00000000000000000000000000100110"),	 -- 346	38
	 ("00000000000000000000000000011100"),	 -- 345	28
	 ("00000000000000000000000000010010"),	 -- 344	18
	 ("00000000000000000000000000001000"),	 -- 343	8
	 ("00000000000000000000000001111101"),	 -- 342	125
	 ("00000000000000000000000001110011"),	 -- 341	115
	 ("00000000000000000000000001101001"),	 -- 340	105
	 ("00000000000000000000000001011111"),	 -- 339	95
	 ("00000000000000000000000001010101"),	 -- 338	85
	 ("00000000000000000000000001001011"),	 -- 337	75
	 ("00000000000000000000000001000001"),	 -- 336	65
	 ("00000000000000000000000000110111"),	 -- 335	55
	 ("00000000000000000000000000101101"),	 -- 334	45
	 ("00000000000000000000000000100011"),	 -- 333	35
	 ("00000000000000000000000000011001"),	 -- 332	25
	 ("00000000000000000000000000001111"),	 -- 331	15
	 ("00000000000000000000000000000101"),	 -- 330	5
	 ("00000000000000000000000001111010"),	 -- 329	122
	 ("00000000000000000000000001110000"),	 -- 328	112
	 ("00000000000000000000000001100110"),	 -- 327	102
	 ("00000000000000000000000001011100"),	 -- 326	92
	 ("00000000000000000000000001010010"),	 -- 325	82
	 ("00000000000000000000000001001000"),	 -- 324	72
	 ("00000000000000000000000000111110"),	 -- 323	62
	 ("00000000000000000000000000110100"),	 -- 322	52
	 ("00000000000000000000000000101010"),	 -- 321	42
	 ("00000000000000000000000000100000"),	 -- 320	32
	 ("00000000000000000000000000010110"),	 -- 319	22
	 ("00000000000000000000000000001100"),	 -- 318	12
	 ("00000000000000000000000000000010"),	 -- 317	2
	 ("00000000000000000000000001110111"),	 -- 316	119
	 ("00000000000000000000000001101101"),	 -- 315	109
	 ("00000000000000000000000001100011"),	 -- 314	99
	 ("00000000000000000000000001011001"),	 -- 313	89
	 ("00000000000000000000000001001111"),	 -- 312	79
	 ("00000000000000000000000001000101"),	 -- 311	69
	 ("00000000000000000000000000111011"),	 -- 310	59
	 ("00000000000000000000000000110001"),	 -- 309	49
	 ("00000000000000000000000000100111"),	 -- 308	39
	 ("00000000000000000000000000011101"),	 -- 307	29
	 ("00000000000000000000000000010011"),	 -- 306	19
	 ("00000000000000000000000000001001"),	 -- 305	9
	 ("00000000000000000000000001111110"),	 -- 304	126
	 ("00000000000000000000000001110100"),	 -- 303	116
	 ("00000000000000000000000001101010"),	 -- 302	106
	 ("00000000000000000000000001100000"),	 -- 301	96
	 ("00000000000000000000000001010110"),	 -- 300	86
	 ("00000000000000000000000001001100"),	 -- 299	76
	 ("00000000000000000000000001000010"),	 -- 298	66
	 ("00000000000000000000000000111000"),	 -- 297	56
	 ("00000000000000000000000000101110"),	 -- 296	46
	 ("00000000000000000000000000100100"),	 -- 295	36
	 ("00000000000000000000000000011010"),	 -- 294	26
	 ("00000000000000000000000000010000"),	 -- 293	16
	 ("00000000000000000000000000000110"),	 -- 292	6
	 ("00000000000000000000000001111011"),	 -- 291	123
	 ("00000000000000000000000001110001"),	 -- 290	113
	 ("00000000000000000000000001100111"),	 -- 289	103
	 ("00000000000000000000000001011101"),	 -- 288	93
	 ("00000000000000000000000001010011"),	 -- 287	83
	 ("00000000000000000000000001001001"),	 -- 286	73
	 ("00000000000000000000000000111111"),	 -- 285	63
	 ("00000000000000000000000000110101"),	 -- 284	53
	 ("00000000000000000000000000101011"),	 -- 283	43
	 ("00000000000000000000000000100001"),	 -- 282	33
	 ("00000000000000000000000000010111"),	 -- 281	23
	 ("00000000000000000000000000001101"),	 -- 280	13
	 ("00000000000000000000000000000011"),	 -- 279	3
	 ("00000000000000000000000001111000"),	 -- 278	120
	 ("00000000000000000000000001101110"),	 -- 277	110
	 ("00000000000000000000000001100100"),	 -- 276	100
	 ("00000000000000000000000001011010"),	 -- 275	90
	 ("00000000000000000000000001010000"),	 -- 274	80
	 ("00000000000000000000000001000110"),	 -- 273	70
	 ("00000000000000000000000000111100"),	 -- 272	60
	 ("00000000000000000000000000110010"),	 -- 271	50
	 ("00000000000000000000000000101000"),	 -- 270	40
	 ("00000000000000000000000000011110"),	 -- 269	30
	 ("00000000000000000000000000010100"),	 -- 268	20
	 ("00000000000000000000000000001010"),	 -- 267	10
	 ("00000000000000000000000000000000"),	 -- 266	0
	 ("00000000000000000000000001110101"),	 -- 265	117
	 ("00000000000000000000000001101011"),	 -- 264	107
	 ("00000000000000000000000001100001"),	 -- 263	97
	 ("00000000000000000000000001010111"),	 -- 262	87
	 ("00000000000000000000000001001101"),	 -- 261	77
	 ("00000000000000000000000001000011"),	 -- 260	67
	 ("00000000000000000000000000111001"),	 -- 259	57
	 ("00000000000000000000000000101111"),	 -- 258	47
	 ("00000000000000000000000000100101"),	 -- 257	37
	 ("00000000000000000000000000011011"),	 -- 256	27
	 ("00000000000000000000000000010001"),	 -- 255	17
	 ("00000000000000000000000000000111"),	 -- 254	7
	 ("00000000000000000000000001111100"),	 -- 253	124
	 ("00000000000000000000000001110010"),	 -- 252	114
	 ("00000000000000000000000001101000"),	 -- 251	104
	 ("00000000000000000000000001011110"),	 -- 250	94
	 ("00000000000000000000000001010100"),	 -- 249	84
	 ("00000000000000000000000001001010"),	 -- 248	74
	 ("00000000000000000000000001000000"),	 -- 247	64
	 ("00000000000000000000000000110110"),	 -- 246	54
	 ("00000000000000000000000000101100"),	 -- 245	44
	 ("00000000000000000000000000100010"),	 -- 244	34
	 ("00000000000000000000000000011000"),	 -- 243	24
	 ("00000000000000000000000000001110"),	 -- 242	14
	 ("00000000000000000000000000000100"),	 -- 241	4
	 ("00000000000000000000000001111001"),	 -- 240	121
	 ("00000000000000000000000001101111"),	 -- 239	111
	 ("00000000000000000000000001100101"),	 -- 238	101
	 ("00000000000000000000000001011011"),	 -- 237	91
	 ("00000000000000000000000001010001"),	 -- 236	81
	 ("00000000000000000000000001000111"),	 -- 235	71
	 ("00000000000000000000000000111101"),	 -- 234	61
	 ("00000000000000000000000000110011"),	 -- 233	51
	 ("00000000000000000000000000101001"),	 -- 232	41
	 ("00000000000000000000000000011111"),	 -- 231	31
	 ("00000000000000000000000000010101"),	 -- 230	21
	 ("00000000000000000000000000001011"),	 -- 229	11
	 ("00000000000000000000000000000001"),	 -- 228	1
	 ("00000000000000000000000001110110"),	 -- 227	118
	 ("00000000000000000000000001101100"),	 -- 226	108
	 ("00000000000000000000000001100010"),	 -- 225	98
	 ("00000000000000000000000001011000"),	 -- 224	88
	 ("00000000000000000000000001001110"),	 -- 223	78
	 ("00000000000000000000000001000100"),	 -- 222	68
	 ("00000000000000000000000000111010"),	 -- 221	58
	 ("00000000000000000000000000110000"),	 -- 220	48
	 ("00000000000000000000000000100110"),	 -- 219	38
	 ("00000000000000000000000000011100"),	 -- 218	28
	 ("00000000000000000000000000010010"),	 -- 217	18
	 ("00000000000000000000000000001000"),	 -- 216	8
	 ("00000000000000000000000001111101"),	 -- 215	125
	 ("00000000000000000000000001110011"),	 -- 214	115
	 ("00000000000000000000000001101001"),	 -- 213	105
	 ("00000000000000000000000001011111"),	 -- 212	95
	 ("00000000000000000000000001010101"),	 -- 211	85
	 ("00000000000000000000000001001011"),	 -- 210	75
	 ("00000000000000000000000001000001"),	 -- 209	65
	 ("00000000000000000000000000110111"),	 -- 208	55
	 ("00000000000000000000000000101101"),	 -- 207	45
	 ("00000000000000000000000000100011"),	 -- 206	35
	 ("00000000000000000000000000011001"),	 -- 205	25
	 ("00000000000000000000000000001111"),	 -- 204	15
	 ("00000000000000000000000000000101"),	 -- 203	5
	 ("00000000000000000000000001111010"),	 -- 202	122
	 ("00000000000000000000000001110000"),	 -- 201	112
	 ("00000000000000000000000001100110"),	 -- 200	102
	 ("00000000000000000000000001011100"),	 -- 199	92
	 ("00000000000000000000000001010010"),	 -- 198	82
	 ("00000000000000000000000001001000"),	 -- 197	72
	 ("00000000000000000000000000111110"),	 -- 196	62
	 ("00000000000000000000000000110100"),	 -- 195	52
	 ("00000000000000000000000000101010"),	 -- 194	42
	 ("00000000000000000000000000100000"),	 -- 193	32
	 ("00000000000000000000000000010110"),	 -- 192	22
	 ("00000000000000000000000000001100"),	 -- 191	12
	 ("00000000000000000000000000000010"),	 -- 190	2
	 ("00000000000000000000000001110111"),	 -- 189	119
	 ("00000000000000000000000001101101"),	 -- 188	109
	 ("00000000000000000000000001100011"),	 -- 187	99
	 ("00000000000000000000000001011001"),	 -- 186	89
	 ("00000000000000000000000001001111"),	 -- 185	79
	 ("00000000000000000000000001000101"),	 -- 184	69
	 ("00000000000000000000000000111011"),	 -- 183	59
	 ("00000000000000000000000000110001"),	 -- 182	49
	 ("00000000000000000000000000100111"),	 -- 181	39
	 ("00000000000000000000000000011101"),	 -- 180	29
	 ("00000000000000000000000000010011"),	 -- 179	19
	 ("00000000000000000000000000001001"),	 -- 178	9
	 ("00000000000000000000000001111110"),	 -- 177	126
	 ("00000000000000000000000001110100"),	 -- 176	116
	 ("00000000000000000000000001101010"),	 -- 175	106
	 ("00000000000000000000000001100000"),	 -- 174	96
	 ("00000000000000000000000001010110"),	 -- 173	86
	 ("00000000000000000000000001001100"),	 -- 172	76
	 ("00000000000000000000000001000010"),	 -- 171	66
	 ("00000000000000000000000000111000"),	 -- 170	56
	 ("00000000000000000000000000101110"),	 -- 169	46
	 ("00000000000000000000000000100100"),	 -- 168	36
	 ("00000000000000000000000000011010"),	 -- 167	26
	 ("00000000000000000000000000010000"),	 -- 166	16
	 ("00000000000000000000000000000110"),	 -- 165	6
	 ("00000000000000000000000001111011"),	 -- 164	123
	 ("00000000000000000000000001110001"),	 -- 163	113
	 ("00000000000000000000000001100111"),	 -- 162	103
	 ("00000000000000000000000001011101"),	 -- 161	93
	 ("00000000000000000000000001010011"),	 -- 160	83
	 ("00000000000000000000000001001001"),	 -- 159	73
	 ("00000000000000000000000000111111"),	 -- 158	63
	 ("00000000000000000000000000110101"),	 -- 157	53
	 ("00000000000000000000000000101011"),	 -- 156	43
	 ("00000000000000000000000000100001"),	 -- 155	33
	 ("00000000000000000000000000010111"),	 -- 154	23
	 ("00000000000000000000000000001101"),	 -- 153	13
	 ("00000000000000000000000000000011"),	 -- 152	3
	 ("00000000000000000000000001111000"),	 -- 151	120
	 ("00000000000000000000000001101110"),	 -- 150	110
	 ("00000000000000000000000001100100"),	 -- 149	100
	 ("00000000000000000000000001011010"),	 -- 148	90
	 ("00000000000000000000000001010000"),	 -- 147	80
	 ("00000000000000000000000001000110"),	 -- 146	70
	 ("00000000000000000000000000111100"),	 -- 145	60
	 ("00000000000000000000000000110010"),	 -- 144	50
	 ("00000000000000000000000000101000"),	 -- 143	40
	 ("00000000000000000000000000011110"),	 -- 142	30
	 ("00000000000000000000000000010100"),	 -- 141	20
	 ("00000000000000000000000000001010"),	 -- 140	10
	 ("00000000000000000000000000000000"),	 -- 139	0
	 ("00000000000000000000000001110101"),	 -- 138	117
	 ("00000000000000000000000001101011"),	 -- 137	107
	 ("00000000000000000000000001100001"),	 -- 136	97
	 ("00000000000000000000000001010111"),	 -- 135	87
	 ("00000000000000000000000001001101"),	 -- 134	77
	 ("00000000000000000000000001000011"),	 -- 133	67
	 ("00000000000000000000000000111001"),	 -- 132	57
	 ("00000000000000000000000000101111"),	 -- 131	47
	 ("00000000000000000000000000100101"),	 -- 130	37
	 ("00000000000000000000000000011011"),	 -- 129	27
	 ("00000000000000000000000000010001"),	 -- 128	17
	 ("00000000000000000000000000000111"),	 -- 127	7
	 ("00000000000000000000000001111100"),	 -- 126	124
	 ("00000000000000000000000001110010"),	 -- 125	114
	 ("00000000000000000000000001101000"),	 -- 124	104
	 ("00000000000000000000000001011110"),	 -- 123	94
	 ("00000000000000000000000001010100"),	 -- 122	84
	 ("00000000000000000000000001001010"),	 -- 121	74
	 ("00000000000000000000000001000000"),	 -- 120	64
	 ("00000000000000000000000000110110"),	 -- 119	54
	 ("00000000000000000000000000101100"),	 -- 118	44
	 ("00000000000000000000000000100010"),	 -- 117	34
	 ("00000000000000000000000000011000"),	 -- 116	24
	 ("00000000000000000000000000001110"),	 -- 115	14
	 ("00000000000000000000000000000100"),	 -- 114	4
	 ("00000000000000000000000001111001"),	 -- 113	121
	 ("00000000000000000000000001101111"),	 -- 112	111
	 ("00000000000000000000000001100101"),	 -- 111	101
	 ("00000000000000000000000001011011"),	 -- 110	91
	 ("00000000000000000000000001010001"),	 -- 109	81
	 ("00000000000000000000000001000111"),	 -- 108	71
	 ("00000000000000000000000000111101"),	 -- 107	61
	 ("00000000000000000000000000110011"),	 -- 106	51
	 ("00000000000000000000000000101001"),	 -- 105	41
	 ("00000000000000000000000000011111"),	 -- 104	31
	 ("00000000000000000000000000010101"),	 -- 103	21
	 ("00000000000000000000000000001011"),	 -- 102	11
	 ("00000000000000000000000000000001"),	 -- 101	1
	 ("00000000000000000000000001110110"),	 -- 100	118
	 ("00000000000000000000000001101100"),	 -- 99	108
	 ("00000000000000000000000001100010"),	 -- 98	98
	 ("00000000000000000000000001011000"),	 -- 97	88
	 ("00000000000000000000000001001110"),	 -- 96	78
	 ("00000000000000000000000001000100"),	 -- 95	68
	 ("00000000000000000000000000111010"),	 -- 94	58
	 ("00000000000000000000000000110000"),	 -- 93	48
	 ("00000000000000000000000000100110"),	 -- 92	38
	 ("00000000000000000000000000011100"),	 -- 91	28
	 ("00000000000000000000000000010010"),	 -- 90	18
	 ("00000000000000000000000000001000"),	 -- 89	8
	 ("00000000000000000000000001111101"),	 -- 88	125
	 ("00000000000000000000000001110011"),	 -- 87	115
	 ("00000000000000000000000001101001"),	 -- 86	105
	 ("00000000000000000000000001011111"),	 -- 85	95
	 ("00000000000000000000000001010101"),	 -- 84	85
	 ("00000000000000000000000001001011"),	 -- 83	75
	 ("00000000000000000000000001000001"),	 -- 82	65
	 ("00000000000000000000000000110111"),	 -- 81	55
	 ("00000000000000000000000000101101"),	 -- 80	45
	 ("00000000000000000000000000100011"),	 -- 79	35
	 ("00000000000000000000000000011001"),	 -- 78	25
	 ("00000000000000000000000000001111"),	 -- 77	15
	 ("00000000000000000000000000000101"),	 -- 76	5
	 ("00000000000000000000000001111010"),	 -- 75	122
	 ("00000000000000000000000001110000"),	 -- 74	112
	 ("00000000000000000000000001100110"),	 -- 73	102
	 ("00000000000000000000000001011100"),	 -- 72	92
	 ("00000000000000000000000001010010"),	 -- 71	82
	 ("00000000000000000000000001001000"),	 -- 70	72
	 ("00000000000000000000000000111110"),	 -- 69	62
	 ("00000000000000000000000000110100"),	 -- 68	52
	 ("00000000000000000000000000101010"),	 -- 67	42
	 ("00000000000000000000000000100000"),	 -- 66	32
	 ("00000000000000000000000000010110"),	 -- 65	22
	 ("00000000000000000000000000001100"),	 -- 64	12
	 ("00000000000000000000000000000010"),	 -- 63	2
	 ("00000000000000000000000001110111"),	 -- 62	119
	 ("00000000000000000000000001101101"),	 -- 61	109
	 ("00000000000000000000000001100011"),	 -- 60	99
	 ("00000000000000000000000001011001"),	 -- 59	89
	 ("00000000000000000000000001001111"),	 -- 58	79
	 ("00000000000000000000000001000101"),	 -- 57	69
	 ("00000000000000000000000000111011"),	 -- 56	59
	 ("00000000000000000000000000110001"),	 -- 55	49
	 ("00000000000000000000000000100111"),	 -- 54	39
	 ("00000000000000000000000000011101"),	 -- 53	29
	 ("00000000000000000000000000010011"),	 -- 52	19
	 ("00000000000000000000000000001001"),	 -- 51	9
	 ("00000000000000000000000001111110"),	 -- 50	126
	 ("00000000000000000000000001110100"),	 -- 49	116
	 ("00000000000000000000000001101010"),	 -- 48	106
	 ("00000000000000000000000001100000"),	 -- 47	96
	 ("00000000000000000000000001010110"),	 -- 46	86
	 ("00000000000000000000000001001100"),	 -- 45	76
	 ("00000000000000000000000001000010"),	 -- 44	66
	 ("00000000000000000000000000111000"),	 -- 43	56
	 ("00000000000000000000000000101110"),	 -- 42	46
	 ("00000000000000000000000000100100"),	 -- 41	36
	 ("00000000000000000000000000011010"),	 -- 40	26
	 ("00000000000000000000000000010000"),	 -- 39	16
	 ("00000000000000000000000000000110"),	 -- 38	6
	 ("00000000000000000000000001111011"),	 -- 37	123
	 ("00000000000000000000000001110001"),	 -- 36	113
	 ("00000000000000000000000001100111"),	 -- 35	103
	 ("00000000000000000000000001011101"),	 -- 34	93
	 ("00000000000000000000000001010011"),	 -- 33	83
	 ("00000000000000000000000001001001"),	 -- 32	73
	 ("00000000000000000000000000111111"),	 -- 31	63
	 ("00000000000000000000000000110101"),	 -- 30	53
	 ("00000000000000000000000000101011"),	 -- 29	43
	 ("00000000000000000000000000100001"),	 -- 28	33
	 ("00000000000000000000000000010111"),	 -- 27	23
	 ("00000000000000000000000000001101"),	 -- 26	13
	 ("00000000000000000000000000000011"),	 -- 25	3
	 ("00000000000000000000000001111000"),	 -- 24	120
	 ("00000000000000000000000001101110"),	 -- 23	110
	 ("00000000000000000000000001100100"),	 -- 22	100
	 ("00000000000000000000000001011010"),	 -- 21	90
	 ("00000000000000000000000001010000"),	 -- 20	80
	 ("00000000000000000000000001000110"),	 -- 19	70
	 ("00000000000000000000000000111100"),	 -- 18	60
	 ("00000000000000000000000000110010"),	 -- 17	50
	 ("00000000000000000000000000101000"),	 -- 16	40
	 ("00000000000000000000000000011110"),	 -- 15	30
	 ("00000000000000000000000000010100"),	 -- 14	20
	 ("00000000000000000000000000001010"),	 -- 13	10
	 ("00000000000000000000000000000000"),	 -- 12	0
	 ("00000000000000000000000001110101"),	 -- 11	117
	 ("00000000000000000000000001101011"),	 -- 10	107
	 ("00000000000000000000000001100001"),	 -- 9	97
	 ("00000000000000000000000001010111"),	 -- 8	87
	 ("00000000000000000000000001001101"),	 -- 7	77
	 ("00000000000000000000000001000011"),	 -- 6	67
	 ("00000000000000000000000000111001"),	 -- 5	57
	 ("00000000000000000000000000101111"),	 -- 4	47
	 ("00000000000000000000000000100101"),	 -- 3	37
	 ("00000000000000000000000000011011"),	 -- 2	27
	 ("00000000000000000000000000010001"),	 -- 1	17
	 ("00000000000000000000000000000111"));	 -- 0	7

begin
  process (clk)
  begin
    if (clk'event and clk = '1') then
      if (we = '1') then
        RAM(conv_integer(address)) <= data_in;
        data_out <= RAM(conv_integer(read_a));
      elsif (oe = '1') then
        data_out <= RAM(conv_integer(read_a));
      end if;
      read_a <= address;
    end if;
  end process;
end rtl;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity block_ram_stepSizeTable is
generic(
	data_width : integer := 8;
	address_width : integer := 8
);
port(
	data_in : in std_logic_vector(data_width-1 downto 0) := (others => '0');
	address : in std_logic_vector(address_width-1 downto 0);
	we: in std_logic := '0';
	oe: in std_logic := '1';
	clk : in std_logic;
	data_out : out std_logic_vector(data_width-1 downto 0));
end block_ram_stepSizeTable;

architecture rtl of block_ram_stepSizeTable is

constant mem_depth : integer := 2**address_width;
type ram_type is array (mem_depth-1 downto 0)
of std_logic_vector (data_width-1 downto 0);

signal read_a : std_logic_vector(address_width-1 downto 0);
signal RAM : ram_type := ram_type'(
	 ("00000000000000000000000000000000"),	 -- 127	0
	 ("00000000000000000000000000000000"),	 -- 126	0
	 ("00000000000000000000000000000000"),	 -- 125	0
	 ("00000000000000000000000000000000"),	 -- 124	0
	 ("00000000000000000000000000000000"),	 -- 123	0
	 ("00000000000000000000000000000000"),	 -- 122	0
	 ("00000000000000000000000000000000"),	 -- 121	0
	 ("00000000000000000000000000000000"),	 -- 120	0
	 ("00000000000000000000000000000000"),	 -- 119	0
	 ("00000000000000000000000000000000"),	 -- 118	0
	 ("00000000000000000000000000000000"),	 -- 117	0
	 ("00000000000000000000000000000000"),	 -- 116	0
	 ("00000000000000000000000000000000"),	 -- 115	0
	 ("00000000000000000000000000000000"),	 -- 114	0
	 ("00000000000000000000000000000000"),	 -- 113	0
	 ("00000000000000000000000000000000"),	 -- 112	0
	 ("00000000000000000000000000000000"),	 -- 111	0
	 ("00000000000000000000000000000000"),	 -- 110	0
	 ("00000000000000000000000000000000"),	 -- 109	0
	 ("00000000000000000000000000000000"),	 -- 108	0
	 ("00000000000000000000000000000000"),	 -- 107	0
	 ("00000000000000000000000000000000"),	 -- 106	0
	 ("00000000000000000000000000000000"),	 -- 105	0
	 ("00000000000000000000000000000000"),	 -- 104	0
	 ("00000000000000000000000000000000"),	 -- 103	0
	 ("00000000000000000000000000000000"),	 -- 102	0
	 ("00000000000000000000000000000000"),	 -- 101	0
	 ("00000000000000000000000000000000"),	 -- 100	0
	 ("00000000000000000000000000000000"),	 -- 99	0
	 ("00000000000000000000000000000000"),	 -- 98	0
	 ("00000000000000000000000000000000"),	 -- 97	0
	 ("00000000000000000000000000000000"),	 -- 96	0
	 ("00000000000000000000000000000000"),	 -- 95	0
	 ("00000000000000000000000000000000"),	 -- 94	0
	 ("00000000000000000000000000000000"),	 -- 93	0
	 ("00000000000000000000000000000000"),	 -- 92	0
	 ("00000000000000000000000000000000"),	 -- 91	0
	 ("00000000000000000000000000000000"),	 -- 90	0
	 ("00000000000000000000000000000000"),	 -- 89	0
	 ("00000000000000000111111111111111"),	 -- 88	32767
	 ("00000000000000000111010001100010"),	 -- 87	29794
	 ("00000000000000000110100111001110"),	 -- 86	27086
	 ("00000000000000000110000000101111"),	 -- 85	24623
	 ("00000000000000000101011101110001"),	 -- 84	22385
	 ("00000000000000000100111101111110"),	 -- 83	20350
	 ("00000000000000000100100001000100"),	 -- 82	18500
	 ("00000000000000000100000110110010"),	 -- 81	16818
	 ("00000000000000000011101110111001"),	 -- 80	15289
	 ("00000000000000000011011001001011"),	 -- 79	13899
	 ("00000000000000000011000101011011"),	 -- 78	12635
	 ("00000000000000000010110011011111"),	 -- 77	11487
	 ("00000000000000000010100011001010"),	 -- 76	10442
	 ("00000000000000000010010100010101"),	 -- 75	9493
	 ("00000000000000000010000110110110"),	 -- 74	8630
	 ("00000000000000000001111010100101"),	 -- 73	7845
	 ("00000000000000000001101111011100"),	 -- 72	7132
	 ("00000000000000000001100101010100"),	 -- 71	6484
	 ("00000000000000000001011100000110"),	 -- 70	5894
	 ("00000000000000000001010011101110"),	 -- 69	5358
	 ("00000000000000000001001100000111"),	 -- 68	4871
	 ("00000000000000000001000101001100"),	 -- 67	4428
	 ("00000000000000000000111110111010"),	 -- 66	4026
	 ("00000000000000000000111001001100"),	 -- 65	3660
	 ("00000000000000000000110011111111"),	 -- 64	3327
	 ("00000000000000000000101111010000"),	 -- 63	3024
	 ("00000000000000000000101010111101"),	 -- 62	2749
	 ("00000000000000000000100111000011"),	 -- 61	2499
	 ("00000000000000000000100011100000"),	 -- 60	2272
	 ("00000000000000000000100000010010"),	 -- 59	2066
	 ("00000000000000000000011101010110"),	 -- 58	1878
	 ("00000000000000000000011010101011"),	 -- 57	1707
	 ("00000000000000000000011000010000"),	 -- 56	1552
	 ("00000000000000000000010110000011"),	 -- 55	1411
	 ("00000000000000000000010100000010"),	 -- 54	1282
	 ("00000000000000000000010010001110"),	 -- 53	1166
	 ("00000000000000000000010000100100"),	 -- 52	1060
	 ("00000000000000000000001111000011"),	 -- 51	963
	 ("00000000000000000000001101101100"),	 -- 50	876
	 ("00000000000000000000001100011100"),	 -- 49	796
	 ("00000000000000000000001011010100"),	 -- 48	724
	 ("00000000000000000000001010010010"),	 -- 47	658
	 ("00000000000000000000001001010110"),	 -- 46	598
	 ("00000000000000000000001000100000"),	 -- 45	544
	 ("00000000000000000000000111101110"),	 -- 44	494
	 ("00000000000000000000000111000001"),	 -- 43	449
	 ("00000000000000000000000110011000"),	 -- 42	408
	 ("00000000000000000000000101110011"),	 -- 41	371
	 ("00000000000000000000000101010001"),	 -- 40	337
	 ("00000000000000000000000100110011"),	 -- 39	307
	 ("00000000000000000000000100010111"),	 -- 38	279
	 ("00000000000000000000000011111101"),	 -- 37	253
	 ("00000000000000000000000011100110"),	 -- 36	230
	 ("00000000000000000000000011010001"),	 -- 35	209
	 ("00000000000000000000000010111110"),	 -- 34	190
	 ("00000000000000000000000010101101"),	 -- 33	173
	 ("00000000000000000000000010011101"),	 -- 32	157
	 ("00000000000000000000000010001111"),	 -- 31	143
	 ("00000000000000000000000010000010"),	 -- 30	130
	 ("00000000000000000000000001110110"),	 -- 29	118
	 ("00000000000000000000000001101011"),	 -- 28	107
	 ("00000000000000000000000001100001"),	 -- 27	97
	 ("00000000000000000000000001011000"),	 -- 26	88
	 ("00000000000000000000000001010000"),	 -- 25	80
	 ("00000000000000000000000001001001"),	 -- 24	73
	 ("00000000000000000000000001000010"),	 -- 23	66
	 ("00000000000000000000000000111100"),	 -- 22	60
	 ("00000000000000000000000000110111"),	 -- 21	55
	 ("00000000000000000000000000110010"),	 -- 20	50
	 ("00000000000000000000000000101101"),	 -- 19	45
	 ("00000000000000000000000000101001"),	 -- 18	41
	 ("00000000000000000000000000100101"),	 -- 17	37
	 ("00000000000000000000000000100010"),	 -- 16	34
	 ("00000000000000000000000000011111"),	 -- 15	31
	 ("00000000000000000000000000011100"),	 -- 14	28
	 ("00000000000000000000000000011001"),	 -- 13	25
	 ("00000000000000000000000000010111"),	 -- 12	23
	 ("00000000000000000000000000010101"),	 -- 11	21
	 ("00000000000000000000000000010011"),	 -- 10	19
	 ("00000000000000000000000000010001"),	 -- 9	17
	 ("00000000000000000000000000010000"),	 -- 8	16
	 ("00000000000000000000000000001110"),	 -- 7	14
	 ("00000000000000000000000000001101"),	 -- 6	13
	 ("00000000000000000000000000001100"),	 -- 5	12
	 ("00000000000000000000000000001011"),	 -- 4	11
	 ("00000000000000000000000000001010"),	 -- 3	10
	 ("00000000000000000000000000001001"),	 -- 2	9
	 ("00000000000000000000000000001000"),	 -- 1	8
	 ("00000000000000000000000000000111"));	 -- 0	7

begin
  process (clk)
  begin
    if (clk'event and clk = '1') then
      if (we = '1') then
        RAM(conv_integer(address)) <= data_in;
        data_out <= RAM(conv_integer(read_a));
      elsif (oe = '1') then
        data_out <= RAM(conv_integer(read_a));
      end if;
      read_a <= address;
    end if;
  end process;
end rtl;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity block_ram_indexTable is
generic(
	data_width : integer := 8;
	address_width : integer := 8
);
port(
	data_in : in std_logic_vector(data_width-1 downto 0) := (others => '0');
	address : in std_logic_vector(address_width-1 downto 0);
	we: in std_logic := '0';
	oe: in std_logic := '1';
	clk : in std_logic;
	data_out : out std_logic_vector(data_width-1 downto 0));
end block_ram_indexTable;

architecture rtl of block_ram_indexTable is

constant mem_depth : integer := 2**address_width;
type ram_type is array (mem_depth-1 downto 0)
of std_logic_vector (data_width-1 downto 0);

signal read_a : std_logic_vector(address_width-1 downto 0);
signal RAM : ram_type := ram_type'(
	 ("00000000000000000000000000001000"),	 -- 15	8
	 ("00000000000000000000000000000110"),	 -- 14	6
	 ("00000000000000000000000000000100"),	 -- 13	4
	 ("00000000000000000000000000000010"),	 -- 12	2
	 ("11111111111111111111111111111111"),	 -- 11	-1
	 ("11111111111111111111111111111111"),	 -- 10	-1
	 ("11111111111111111111111111111111"),	 -- 9	-1
	 ("11111111111111111111111111111111"),	 -- 8	-1
	 ("00000000000000000000000000001000"),	 -- 7	8
	 ("00000000000000000000000000000110"),	 -- 6	6
	 ("00000000000000000000000000000100"),	 -- 5	4
	 ("00000000000000000000000000000010"),	 -- 4	2
	 ("11111111111111111111111111111111"),	 -- 3	-1
	 ("11111111111111111111111111111111"),	 -- 2	-1
	 ("11111111111111111111111111111111"),	 -- 1	-1
	 ("11111111111111111111111111111111"));	 -- 0	-1

begin
  process (clk)
  begin
    if (clk'event and clk = '1') then
      if (we = '1') then
        RAM(conv_integer(address)) <= data_in;
        data_out <= RAM(conv_integer(read_a));
      elsif (oe = '1') then
        data_out <= RAM(conv_integer(read_a));
      end if;
      read_a <= address;
    end if;
  end process;
end rtl;
