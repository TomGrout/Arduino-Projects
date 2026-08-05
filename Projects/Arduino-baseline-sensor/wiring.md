Display Physical Pin	Internal Function	    Connect to Arduino Pin
Pin 12 (Top Left)	    Digit 1                 Control	Arduino Pin 9
Pin 11 (Top Row)	    Segment A	            Arduino Pin 2
Pin 10 (Top Row)	    Segment F	            Arduino Pin 7
Pin 9 (Top Row)	        Digit 2 Control	        Arduino Pin 10
Pin 8 (Top Row)	        Digit 3 Control	        Arduino Pin 11
Pin 7 (Top Right)	    Segment B	            Arduino Pin 3
Pin 6 (Bottom Right)	Digit 4 Control	        Arduino Pin 12
Pin 5 (Bottom Row)	    Segment G	            Arduino Pin 8
Pin 4 (Bottom Row)	    Segment C	            Arduino Pin 4
Pin 3 (Bottom Row)	    Decimal Point (DP)	    Unused (Leave disconnected)
Pin 2 (Bottom Row)	    Segment D	            Arduino Pin 5
Pin 1 (Bottom Left)	    Segment E	            Arduino Pin 6


    Top Pins (12, 11, 10, 9, 8, 7)
    +----------------------------------+
    |  D1   A   F   D2  D3   B         |
    |                                  |
    |               8.8.8.8.           |     <-- 4 digit 7 segment display
    |                                  |
    |  E    D   DP  C   G   D4         |
    +----------------------------------+
     Bottom Pins (1, 2, 3, 4, 5, 6)

