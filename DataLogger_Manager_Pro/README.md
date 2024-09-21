<h1>DataLogger Manager Pro</h1>
<p><strong>DataLogger Manager Pro</strong> is a C program designed to manage and process data from logging systems. It allows users to read, filter, and manipulate the data stored in files like <code>dataloger.txt</code> and <code>ciachovanie.txt</code>.</p>
<h2>Key Features</h2>
<ul>
<li>View logged data in a structured format</li>
<li>Load data from files into arrays for processing</li>
<li>Filter data based on calibration intervals</li>
<li>Search and sort data by specific criteria (e.g., IDs, types)</li>
<li>Generate statistical reports on measurement types</li>
<li>Delete specific records from the dataset</li>
<li>Clear memory and exit the program</li>
</ul>
<h2>Command Overview</h2>
<p>The program accepts the following commands:</p>
<div class="commands">
<p><strong>v</strong> - View data directly from the file or loaded array.</p>
<p><strong>n</strong> - Load data from the <code>dataloger.txt</code> file into an array.</p>
<p><strong>c</strong> - Filter records by calibration intervals specified in the <code>ciachovanie.txt</code> file.</p>
<p><strong>s</strong> - Search and sort records by ID and type, saving the sorted results to <code>vystup_S.txt</code>.</p>
<p><strong>h</strong> - Generate a report on the frequency, minimum, and maximum values of specific measurement types (e.g., RD, RM, RO).</p>
<p><strong>z</strong> - Delete a specific record from the dataset by ID.</p>
<p><strong>k</strong> - Clear all allocated memory and exit the program.</p>
</div>
<h2>File Structure</h2>
<p>The program relies on two files:</p>
<ul>
<li><strong>dataloger.txt</strong> - Contains the main data logs in the following format:</li>
<pre>
ID (e.g., A111a)
Position (e.g., +481234+194567)
Type (e.g., RD)
Value (e.g., 125.36)
Time (e.g., 1255)
Date (e.g., 20231010)
</pre>
<li><strong>ciachovanie.txt</strong> - Contains calibration data with the following structure:</li>
<pre>
ID (e.g., A111a)
Calibration date (e.g., 20230801)
</pre>
</ul>
<h2>How to Run the Program</h2>
<p>To compile and run the program, follow these steps:</p>
<ol>
<li>Ensure that the <code>dataloger.txt</code> and <code>ciachovanie.txt</code> files are present in the working directory.</li>
<li>Use a C compiler to compile the program. For example, run the following command:</li>
<pre>gcc -o datalogger_manager_pro datalogger_manager_pro.c</pre>
<li>Run the program with the following command:</li>
<pre>./datalogger_manager_pro</pre>
<li>Enter the desired command when prompted (e.g., <code>v</code>, <code>n</code>, <code>c</code>, etc.).</li>
</ol>
<h2>Example Usage</h2>
<p>Below is an example session with the program:</p>
<pre>
Zadajte prikaz (v/n/c/s/h/z/k): n
Data loaded from dataloger.txt.
Zadajte prikaz (v/n/c/s/h/z/k): c
Enter calibration month: 3
Filtering data for calibration...
ID. mer. modulu [A111a] ma 2 mesiacov po ciachovani
ID. mer. modulu [A111b] ma 4 mesiacov po ciachovani
ID. mer. modulu [B151a] nie je ciachovany.
Zadajte prikaz (v/n/c/s/h/z/k): k
Memory cleared. Exiting program.
</pre>
<h2>Memory Management</h2>
<p>The program dynamically allocates memory for arrays used to store data from files. It is important to free this memory before exiting the program, which is handled by the <code>k</code> command. Always use the <code>k</code> command to properly release resources.</p>
<br />
<p><em>Developed by Vladyslav Pilkevych, 2023</em></p>
