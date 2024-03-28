Example Data

DATE,CODE,PUBLISHER,TITLE,PRICE
03/08/23,JAN231097,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover A Letizia Cadonici),$3.99 
03/08/23,JAN231098,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover B Keyla Valerio),$3.99 
03/08/23,JAN231099,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover C Fritz Casis Giant-Size X-Men #1 Homage Variant),$3.99 
03/08/23,JAN231100,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover D Letizia Cadonici Virgin Variant),AR
03/08/23,JAN231101,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover E Keyla Valerio Virgin Variant),AR
03/08/23,JAN231102,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover F Fritz Casis Giant-Size X-Men #1 Homage Virgin Variant),AR
03/08/23,DEC220991,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover A Roberto Meli),$3.99 
03/08/23,DEC220992,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover B Emilio Pilliu),$3.99 
03/08/23,DEC220993,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover C Alessandro Amoruso),$3.99 
03/08/23,DEC220994,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover D Brent McKee Marvel Premiere #1 Warlock Homage Variant),$3.99 
The data starts with a header line that should be ignored, i.e. it is not stored in the array of comics.

If you look at the 4-6th comics you can see the cost for those is listed as AR which means the cost has not been set yet.

When you read this data in, you should use character arrays, also called buffers, that are large enough to store any length for the field. Then when you store the field in the struct, you must size the string to be as short as possible to store just what is needed. For example, if your buffer is 1000 characters long, but the title is only 100 characters long then you will create, dynamically, a string to store the 100 characters. (Don’t forget to leave space for the null terminator).

Commands
load

The load command should read in each line of the csv file and store it into a Comic. That Comic should then be put into the Comic_List representing all of the comics in the current csv file.

buy

The buy command should add the comic at a given list position to another list containing all of the comics we wish to buy. You will have one list representing all the comics in the loaded csv file and another list representing just the comics you wish to buy. If load is called multiple times before clear, you will just keep increasing the size of the list. Consider whether you should use a deep copy or a shallow copy when adding to the purchase list.

checkout

The checkout command will purchase all of the comics in the list of comics we wish to buy. They should be printed along with a receipt with the subtotal, tax (5%) and total after tax. Note that this command does not affect any comics loaded into the list representing the current csv file. The purchase list will be empty after this command runs. Comics with "AR" listed as the price will still be printed in the output file but will not be added to the subtotal of the purchase.

display

The display command will display or output each comic in turn from the list into the output file. See the example output for how you are to display the comic. Note: Updated output for when the list is empty. See zip file for example.

save

The save command will write the current list of comics into the file that is given file. The format should match the format of the original csv file. You should be able to load, then save, and then load the newly created file without a difference.

clear

This empties the list. Be careful to make sure you don’t lose memory.

find

This will be given a potential index in the list. If the index is valid, then you will display the information about the comic at the given index position.

remove

This will be given a potential index in the list. If the index is valid, then the comic at that index will be remove and the comics at indices that are higher than the given index will all be shifted down 1 index position. Be careful to clean up your memory.
