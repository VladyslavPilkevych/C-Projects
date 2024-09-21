<h1>Measurement Data Processing and Module Sorting</h1>
<h2>Project Description</h2>
<p>
This project implements a system for managing and processing measurement module data. It includes two key features:
</p>
<ul>
<li>
<strong>Module ID Validation:</strong> 
The program ensures that user-entered module IDs follow a strict format (A-Z, 001-999, a-z). If an invalid ID is entered, it prompts the user to correct it.
</li>
<li>
<strong>Measurement Data Sorting and Analysis:</strong> 
The program can process measurement data, find the minimum and maximum values, count occurrences, and calculate the median. It also includes a check for outliers, ensuring data falls within an acceptable range.
</li>
</ul>
<h2>Functionality</h2>
<h3>Module ID Validation</h3>
<p>
The user is prompted to enter a module ID, which must be in the format: a capital letter (A-Z), followed by three digits (001-999), and a lowercase letter (a-z). If the ID is invalid, the program continues to ask for a correct ID until the proper format is followed.
</p>
<h3>Measurement Data Sorting and Analysis</h3>
<p>
The program accepts measurement data and groups it by module ID and measurement type. It calculates the minimum and maximum values for each group, along with the median and the percentage differences from the median. If any values exceed a specified threshold, the program alerts the user.
</p>
<h2>How to Use the Program</h2>
<ol>
<li>Run the program.</li>
<li>Enter a valid measurement module ID (A-Z, 001-999, a-z).</li>
<li>Provide the type of measurement variable (RD, RM, RO, PI, PE, PA).</li>
<li>The program processes and outputs statistical information for the selected module.</li>
<li>For data analysis, press 'j' for detailed statistics or 't' for a summary of all modules.</li>
</ol>
<h2>Program Example</h2>
<h3>Module ID Validation</h3>
<pre>
Enter the module ID (A-Z, 001-999, a-z): A123b
Your ID is: A123b
Correct module ID: A123b
</pre>
<h3>Measurement Data Analysis</h3>
<pre>
Enter type of measurement variable (RD, RM, RO, PI, PE, PA): RM
Correctly entered type: RM

Calculating...
Type        Occurrences    Minimum     Maximum   Median    Min %    Max %
A123b       5              12.50       99.99     56.75     -34.57   +45.12
A123b is within the standard deviation range.
</pre>
<h2>Additional Information</h2>
<p>
The project is written in C and handles dynamic memory allocation for storing and processing a large set of measurement data. It also implements a bubble sort algorithm for arranging the data and calculating statistical values such as the median. The program provides two modes: one for detailed analysis of specific module IDs and another for summarizing all data entries.
</p>
<br />
<p><em>Developed by Vladyslav Pilkevych, 2023</em></p>
