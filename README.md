# udf_json说明

mysql udf插件，基于rapidjson开发用以解析或打包json体，主要用于企业中mysql5.6以及以下喜欢用text来存json的场景(珍惜生命,爱护环境,请使用mysql5.7:))

- [x] 支持uri片段语法来来获取json指定value
- [x] 支持uri片段来获取json的array的元素数目

------
# 编译

cd udf_json

mkdir build

cmake ..

make

# 安装

cp ./libudf_json.so /usr/local/mysql/lib/plugin/

mysql -uxxx -pxxx -hxxx -Pxxx

```SQL
drop function udf_json_get_value;
drop function udf_json_array_length;
create function udf_json_get_value returns string soname 'libudf_json.so';
create function udf_json_array_length returns integer soname 'libudf_json.so';
```

# 使用示例
```SQL
SET @test_json='{
	"name": "lily",
	"age": 18,
	"friend": [{
		"name": "lucy",
		"age": 17
	}, {
		"name": "lilei",
		"age": 18
	}]
}';
SELECT udf_json_get_value(@test_json, '/name');
"lily"

SELECT udf_json_get_value(@test_json, '/friend/0/name');
"lucy"

SELECT udf_json_array_length(@test_json, '/friend');
2
```

# uri说明
```JSON
{
    "foo":["bar":"baz"],
    "pi":3.14
}
```
> * "/foo" -> ["bar":"baz"]
> * "/foo/0" -> "bar"
> * "/foo/1" -> "baz"
> * "pi" -> 3.14

### uri表示方式

| 字符串表示方式  | Pointer Tokens
| :------------:  | :--------:
|"/foo/0"         | {"foo",0}
|"a~1b"           | {"a/b"}
|"/m~0n"          | {"m~n"}
|"/ "             | {" "}
|"/\0"            | {"\0"}
|"/€"             | {"€"}
 

