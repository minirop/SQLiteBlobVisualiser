# SQLiteBrowser

A SQLite viewer that can have plugins to visualise specific data in BLOB fields.

## Plugins

The plugins inherit from [BlobInterface](browser/include/blobinterface.h) that has several pure virtual methods.

* name: the name used in [plugins.ini](bin/plugins.ini) (see below)
* supportedTypes: List of types that plugin can process
* process: as the name implies, process the data.

## Configuration

The file [plugins.ini](bin/plugins.ini) contains the mapping between table/field couple to plugin(s). Sample:

```
[table_name]
field_name=plugin1,plugin1,plugin3
other_field=plugin1

[other_table]
field_name=...
...
```

Before showing the data of a field, it will be process by each plugin in the order they are defined in the setting file. (e.g. `field_name` in `table_name` will be transform as `output = plugin3(plugin2(plugin1(data)))`).

## Usage

* Launch the sofware
* File > Open database: will show the tables of the database on the left
* Double-click on a table: will show the content of this table on the right
* Double-click on a cell: if it's showing `BLOB`, process it as defined, else just show it directly.
