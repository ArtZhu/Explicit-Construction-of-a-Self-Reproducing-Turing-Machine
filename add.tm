100111001    101  101 11010
~
10000
~
10000 0 10000 0 R
10000 1 10000 1 R
10000 B 10001 B R
10001 B 10001 B R
10001 0 10002 0 R
10001 1 10002 1 R
10002 0 10002 0 R
10002 1 10002 1 R
10002 B 10003 B R
10003 0 10002 0 R
10003 1 10002 1 R
10003 B 10004 B R
10004 0 10002 0 R
10004 1 10002 1 R
10004 B 10005 B L
10005 B 0 B L
###
0 B 1 1 L
1 0 1 0 L
1 1 1 1 L
## pass all
1 B 2 B L
2 0 2 0 L
2 1 2 1 L
2 B 3 B L
3 0 2 0 L
3 1 2 1 L
3 B 4 B L
4 0 2 0 L
4 1 2 1 L
4 B 5 B L
5 B 5 B L
5 0 6 0 L
5 1 6 1 L
6 0 6 0 L
6 1 6 1 L
6 B 7 B R
## digit 0
7 0 33 B R
33 0 33 0 R
33 1 33 1 R
33 B 34 B R
## pass all
34 B 34 B R
34 0 35 0 R
34 1 35 1 R
35 0 35 0 R
35 1 35 1 R
35 B 36 B R
36 0 35 0 R
36 1 35 1 R
36 B 37 B R
37 0 35 0 R
37 1 35 1 R
37 B 38 B L
38 B 39 B L
39 B 40 B L
40 1 41 1 L
41 0 50 B L
41 1 22 B L
## digit 1
7 1 13 B R
13 0 13 0 R
13 1 13 1 R
13 B 14 B R
## pass all
14 B 14 B R
14 0 15 0 R
14 1 15 1 R
15 0 15 0 R
15 1 15 1 R
15 B 16 B R
16 0 15 0 R
16 1 15 1 R
16 B 17 B R
17 0 15 0 R
17 1 15 1 R
17 B 18 B L
18 B 19 B L
19 B 20 B L
20 1 21 1 L
## 0 finish addition
21 0 22 B L 
## 22 carry 1
## 1 
21 1 32 B L 
## 32 carry 0
32 0 50 1 R
32 1 32 0 L
32 B 43 B R
43 0 44 1 R
44 0 44 0 R
44 B 45 B R
45 0 45 0 R
45 1 45 1 R
45 B 46 B L
46 0 47 B R
46 1 48 B R
47 B 45 0 L
48 B 45 1 L
46 B 50 0 L
## 22 carry 1
## 50 carry 0
## pass all
22 0 22 0 L
22 1 22 1 L
22 B 30 B L
30 0 22 0 L
30 1 22 1 L
30 B 31 B L
31 0 22 0 L
31 1 22 1 L
31 B 23 B L
23 B 23 B L
23 0 24 0 L
23 1 24 1 L
24 0 24 0 L
24 1 24 1 L
24 B 25 B R
## 25
## check right 
25 0 28 0 R
25 1 28 1 R
## if B, ready to halt with carry 1
28 B 210 B L
## else go on
28 0 29 0 L
28 1 29 1 L
## 29 read 0
29 0 26 B R
## 29 read 1
29 1 27 B R
## 50 carry 0
## pass all
50 0 50 0 L
50 1 50 1 L
50 B 56 B L
56 0 50 0 L
56 1 50 1 L
56 B 57 B L
57 0 50 0 L
57 1 50 1 L
57 B 51 B L
51 B 51 B L
51 0 52 0 L
51 1 52 1 L
52 0 52 0 L
52 1 52 1 L
52 B 53 B R
## 53
## check right 
53 0 54 0 R
53 1 54 1 R
## if B, ready to halt with carry 0
54 B 160 B L
## else go on
54 0 55 0 L
54 1 55 1 L
## 55 read 0
55 0 58 B R
## 55 read 1
55 1 59 B R
## 26 -> 60 (carry 1 read 0) -> 60
## pass all
26 0 60 0 R
26 1 60 1 R
60 0 60 0 R
60 1 60 1 R
60 B 61 B R
61 B 61 B R
61 0 62 0 R
61 1 62 1 R
62 0 62 0 R
62 1 62 1 R
62 B 63 B R
63 0 62 0 R
63 1 62 1 R
63 B 64 B R
64 0 62 0 R
64 1 62 1 R
64 B 65 B L
65 B 66 B L
66 B 67 B L
## 67 will read addtional marker 1
67 0 67 0 L
67 1 67 1 L
## rewrite the carried 1
67 B 68 1 L
## goto add machine add 0
68 0 50 B L
## 50 carry 0
68 1 22 B L
## 22 carry 1
## 68 read B move everthing one digit to the right
68 B 100 B R
100 0 100 0 R
100 1 100 1 R
100 B 101 B L
101 0 102 B R
101 1 103 B R
102 B 100 0 L
103 B 100 1 L
101 B 50 B L
##
## 27 -> 70 (carry 1 read 1) -> 70
## pass all
27 0 70 0 R
27 1 70 1 R
70 0 70 0 R
70 1 70 1 R
70 B 71 B R
71 B 71 B R
71 0 72 0 R
71 1 72 1 R
72 0 72 0 R
72 1 72 1 R
72 B 73 B R
73 0 72 0 R
73 1 72 1 R
73 B 74 B R
74 0 72 0 R
74 1 72 1 R
74 B 75 B L
75 B 76 B L
76 B 77 B L
## 77 will read addtional marker 1
77 0 77 0 L
77 1 77 1 L
## rewrite the carried 1
77 B 78 1 L
## goto add machine add 1
#####
## check if still have digit on left
#####
#####
## if have,
## 	goto add machine add 1
78 0 79 0 R
78 1 79 1 R
79 0 121 0 L
79 1 121 1 L
#####
## else move digits one to the right then go
78 B 130 B R
## skip add machine
## carry 1
## at 22
##
## 58 -> 80 (carry 0 read 0) -> 80
## pass all
58 0 80 0 R
58 1 80 1 R
80 0 80 0 R
80 1 80 1 R
80 B 81 B R
81 B 81 B R
81 0 82 0 R
81 1 82 1 R
82 0 82 0 R
82 1 82 1 R
82 B 83 B R
83 0 82 0 R
83 1 82 1 R
83 B 84 B R
84 0 82 0 R
84 1 82 1 R
84 B 85 B L
85 B 86 B L
86 B 87 B L
## 87 will read addtional marker 1
87 0 87 0 L
87 1 87 1 L
## rewrite the carried 0
87 B 88 0 L
## goto add machine add 0
88 0 50 B L
## 50 carry 0
88 1 22 B L
## 22 carry 1
##
## 59 -> 90 (carry 0 read 1) -> 90
## pass all
59 0 90 0 R
59 1 90 1 R
90 0 90 0 R
90 1 90 1 R
90 B 91 B R
91 B 91 B R
91 0 92 0 R
91 1 92 1 R
92 0 92 0 R
92 1 92 1 R
92 B 93 B R
93 0 92 0 R
93 1 92 1 R
93 B 94 B R
94 0 92 0 R
94 1 92 1 R
94 B 95 B L
95 B 96 B L
96 B 97 B L
## 97 will read addtional marker 1
97 0 97 0 L
97 1 97 1 L
## rewrite the carried 0
97 B 98 0 L
#####
## check if still have digit on left
#####
#####
## if have,
## 	goto add machine add 1
98 0 99 0 R
98 1 99 1 R
99 0 121 0 L
99 1 121 1 L
#####
## else move digits one to the right then go
98 B 130 B R
130 0 130 0 R
130 1 130 1 R
130 B 131 B L
131 0 132 B R
131 1 133 B R
132 B 131 0 L
133 B 131 1 L
131 B 134 B R
## skip add machine
## carry 1
134 B 22 B R
##
### add machine
## 0 finish addition
121 0 22 B L 
## 22 carry 1
## digit 1
## 1 
121 1 123 B L 
## 123 carry 0
123 0 50 1 R
123 1 123 0 L
123 B 124 B R
124 0 124 0 R
124 1 124 1 R
124 B 125 B R
125 0 125 0 R
125 1 125 1 R
125 B 126 B L
126 0 127 B R
126 1 128 B R
126 B 129 B R
127 B 125 0 L
128 B 125 1 L
129 B 140 B L
140 B 141 B L
141 0 142 B R
141 1 143 B R
142 B 140 0 L
143 B 140 1 L
141 B 144 B R
144 B 50 1 R
## 22 carry 1
##
## 160 halt state carry 0
160 0 167 B R
160 1 168 B R
## 167 -> 170 (read 0 halt)
## pass all
167 B 167 B R
167 0 170 0 R
167 1 170 1 R
170 0 170 0 R
170 1 170 1 R
170 B 171 B R
171 0 170 0 R
171 1 170 1 R
171 B 172 B R
172 0 170 0 R
172 1 170 1 R
172 B 173 B L
173 B 174 B L
174 B 175 B L
175 0 175 0 L
175 1 175 1 L
175 B 200 0 L
## halt
## 168 -> 180 (read 1 halt)
## pass all
168 B 168 B R
168 0 180 0 R
168 1 180 1 R
180 0 180 0 R
180 1 180 1 R
180 B 181 B R
181 0 180 0 R
181 1 180 1 R
181 B 182 B R
182 0 180 0 R
182 1 180 1 R
182 B 183 B L
183 B 184 B L
184 B 185 B L
185 0 185 0 L
185 1 185 1 L
185 B 186 0 L
## now add machine add 1
## check digit
## if B
##  	move all digits one to right;
186 B 176 B R
176 0 176 0 R
176 1 176 1 R
176 B 177 B L
177 0 178 B R
177 1 179 B R
178 B 176 0 L
179 B 176 1 L
177 B 169 B R
169 B 200 1 R
##
## else go to add machine
186 0 187 0 R
186 1 187 1 R
187 0 190 0 L
187 1 190 1 L
##
### add machine
## 0 finish addition
190 0 200 1 L 
## halt at 200
## digit 1
## 1 
190 1 191 0 L 
## ??? carry 0
191 0 200 1 R
191 1 191 0 L
191 B 192 B R
## write 1 instead of B
192 0 192 0 R
192 1 192 1 R
192 B 195 B L
#194 0 194 0 R
#194 1 194 1 R
#194 B 195 B L
195 0 196 B R
195 1 197 B R
196 B 192 0 L
197 B 192 1 L
195 B 198 B R
198 B 200 1 R
## HALT AT 200
##
## 210 halt state carry 1
210 0 212 B R
210 1 213 B R
## 212 -> 220 (read 0 halt)
## pass all
212 B 212 B R
212 0 220 0 R
212 1 220 1 R
220 0 220 0 R
220 1 220 1 R
220 B 221 B R
221 0 220 0 R
221 1 220 1 R
221 B 222 B R
222 0 220 0 R
222 1 220 1 R
222 B 223 B L
223 B 224 B L
224 B 225 B L
225 0 225 0 L
225 1 225 1 L
225 B 200 0 L
## halt
## 213 -> 230 (read 1 halt)
## pass all
213 B 213 B R
213 0 230 0 R
213 1 230 1 R
230 0 230 0 R
230 1 230 1 R
230 B 231 B R
231 0 230 0 R
231 1 230 1 R
231 B 232 B R
232 0 230 0 R
232 1 230 1 R
232 B 233 B L
233 B 234 B L
234 B 235 B L
235 0 235 0 L
235 1 235 1 L
235 B 236 1 L
## now add machine add 1
## check digit
## if B
##  	move all digits one to right;
236 B 255 B R
255 0 255 0 R
255 1 255 1 R
255 B 256 B L
256 0 257 B R
256 1 258 B R
257 B 255 0 L
258 B 255 1 L
256 B 259 B R
259 B 200 1 R
###############################
##
## else go to add machine
236 0 237 0 R
236 1 237 1 R
237 0 240 0 L
237 1 240 1 L
##
### add machine
## 0 finish addition
240 0 200 1 L 
## halt at 200
## digit 1
## 1 
### write 0 instead of B
240 1 241 0 L 
## ??? carry 0
241 0 200 1 R
241 1 241 0 L
241 B 242 B R
## write 1 instead of B
242 0 242 0 R
242 1 242 1 R
#243 0 243 0 R
#243 1 243 1 R
242 B 245 B L
#244 0 244 0 R
#244 1 244 1 R
#244 B 245 B L
245 0 246 B R
245 1 247 B R
245 0 246 B R
245 1 247 B R
246 B 242 0 L
247 B 242 1 L
245 B 248 B R
248 B 200 1 R
## HALT AT 200
##
## 200 then remove marker 1
200 0 200 0 R
200 1 200 1 R
200 B 250 B L
250 1 251 B L
