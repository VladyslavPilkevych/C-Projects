<h1>Advanced Data Logger V2</h1>
<p><strong>Advanced Data Logger V2</strong> is a C program designed for handling structured data stored in linked lists. It provides users with functionality for inserting, deleting, swapping, and sorting log entries from files like <code>dataloger_V2.txt</code>.</p>
<h2>Key Features</h2>
<ul>
<li>Dynamic linked list structure for data storage</li>
<li>Loading data from files into a linked list</li>
<li>Insert, delete, and swap records by user input</li>
<li>Sort records by date and time</li>
<li>View and print the entire data list</li>
<li>Memory management functions for efficient data handling</li>
</ul>
<h2>Command Overview</h2>
<p>The program accepts the following commands:</p>
<div class="commands">
<p><strong>n</strong> - Load data from <code>dataloger_V2.txt</code> into the linked list.</p>
<p><strong>v</strong> - View all loaded records in the list.</p>
<p><strong>p</strong> - Insert a new record at a specified index.</p>
<p><strong>z</strong> - Delete a record by its ID.</p>
<p><strong>u</strong> - Sort records by date and time in ascending order.</p>
<p><strong>r</strong> - Swap two records based on their index numbers.</p>
<p><strong>k</strong> - Clear the list from memory and exit the program.</p>
</div>
<h2>File Structure</h2>
<p>The program relies on the <code>dataloger_V2.txt</code> file, which stores data in the following format:</p>
<pre>
$$$
ID (e.g., A111a)
Position (e.g., +48.1234+19.4567)
Type (e.g., RD)
Value (e.g., 125.36)
Time (e.g., 1055)
Date (e.g., 20231010)
$$$
</pre>
<p>Each record block is separated by <code>$$$</code>.</p>
<h2>How to Run the Program</h2>
<p>To compile and run the program, follow these steps:</p>
<ol>
<li>Ensure that the <code>dataloger_V2.txt</code> file is in the working directory.</li>
<li>Use a C compiler to compile the program. For example, run the following command:</li>
<pre>gcc -o advanced_datalogger_V2 advanced_datalogger_V2.c</pre>
<li>Run the program with the following command:</li>
<pre>./advanced_datalogger_V2</pre>
<li>Enter the desired command when prompted (e.g., <code>n</code>, <code>v</code>, <code>p</code>, etc.).</li>
</ol>
<h2>Example Usage</h2>
<p>Below is an example session with the program:</p>
<pre>
Zadajte prikaz (n/v/p/z/u/r/k): n
Nacitalo sa 10 zaznamov

Zadajte prikaz (n/v/p/z/u/r/k): v
1.
ID: A111a  RD   125.36
Poz: +48.1234+19.4567
DaC: 2023.10.10 10:55

2.
ID: A111a  RM   185.36
Poz: +48.1784+19.4567
DaC: 2023.10.08 10:25

Zadajte prikaz (n/v/p/z/u/r/k): k
Memory cleared. Exiting program.
</pre>
<h2>Memory Management</h2>
<p>The program dynamically allocates memory for linked list nodes. It is important to free this memory before exiting the program, which is handled by the <code>k</code> command. Always use the <code>k</code> command to properly release resources.</p>
<p><em>Developed by Vladyslav Pilkevych, 2023</em></p>
