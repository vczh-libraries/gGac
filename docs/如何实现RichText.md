# pipeline

* split paragraph into lines by ```\r\n```
* split line into items (itemize text)
* each item is constructed by one or more runs
* build each run by getting glyph and cluster data from corresponding item shape



* example
   
   ```glyphString = item->shape(runText)```
   |||
   |--|--|
   |text|flflflfl
   |||
   |cluster|00112233|
   |||
   |glyph|0 1 2 3|

* runder glyph cluster in cairo context by pango.
