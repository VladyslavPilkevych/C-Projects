<h1>Character Selection and Shrinking Square Drawer</h1>
<h2>Project Description</h2>
<p>
This project consists of two main functionalities:
</p>
<ul>
<li>
<strong>Character Selection:</strong> 
This part of the program allows the user to select and input a character from a specified range of letters (either lowercase or uppercase). The user provides a range of characters and the type (lowercase or uppercase), and the program checks if the entered character falls within the specified range.
</li>
<li>
<strong>Shrinking Square Drawer:</strong> 
The program draws a series of "shrinking squares" using the <code>+</code> symbol for the borders and <code>-</code> for the inner sections. The squares start at a given size and decrease in size at each iteration until the smallest possible square is drawn.
</li>
</ul>
<h2>Functionality</h2>
<h3>Character Selection</h3>
<p>
The user inputs the starting and ending characters of a range, along with the type ('M' for lowercase letters, 'V' for uppercase letters). The program then prompts the user to enter a character and checks if the input is within the specified range. If the input is valid, the program outputs a success message; otherwise, it outputs an error.
</p>
<h3>Shrinking Square Drawer</h3>
<p>
The program prompts the user for the size of the square and then draws a series of shrinking squares. The outer square begins at the provided size, and subsequent squares shrink by two characters at each step until the smallest square is reached. The borders of each square are drawn with <code>+</code> characters, while the inner area is filled with <code>-</code>.
</p>
<h2>How to Use the Program</h2>
<ol>
<li>Run the program.</li>
<li>Enter the starting and ending characters for the range, and the character type ('M' for lowercase or 'V' for uppercase).</li>
<li>Input a character that fits the specified range.</li>
<li>Enter the size of the square for drawing the shrinking squares.</li>
</ol>
<h2>Program Example</h2>
<h3>Character Selection</h3>
<pre>
Enter value for N: a
Enter value for M: z
Enter character type ('M' for lowercase, 'V' for uppercase): M
Enter a lowercase character from the range a,z: c
Character successfully entered, from range a,z, selected lowercase character: c.
</pre>
<h3>Shrinking Square Drawer</h3>
<pre>
Enter the size of the square: 5
+++++
+---+
+---+
+---+
+++++
+++
+-+
+++
+
</pre>
<br />
<p><em>Developed by Vladyslav Pilkevych, 2023</em></p>
