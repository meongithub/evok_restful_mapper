# restful_mapper #

ORM for consuming the unipi evok (semi)RESTful APIs in C++


# Introduction #

**evok\_restful\_mapper** connects business objects and Representational State
Transfer (REST) web services. It implements object-relational mapping for REST
web services to provide transparent proxying capabilities between a client
(using **restful_mapper**) and a RESTful web service (that follows the
conventions outlined below).

The ideas and design philosophy are directly adopted from [Active Resource][3].
However, the API and functionality differ in some areas, where it makes sense.

## Design goals ##
See https://github.com/logandk/restful_mapper

# Building #

**evok\_restful\_mapper** is built using [CMake][6].

## Dependencies ##

The following libraries are required to build **evok_restful_mapper**.

* [libcurl][7] - used for comminucating with the web service over HTTP
* [yajl][8] - used to parse and emit JSON
* [libiconv][9] - used to convert between character sets
* [googletest][10] - required for tests only

Invoking the following command will download and build these libraries.

```shell
make vendor
```

On UNIX platforms, [libcurl][7] and [libiconv][9] are typically present on the
system, and will not be built by the make command. If they are not present,
they should be installed using the system package manager.

## Library ##

After building the dependencies, invoke the following command to build **restful_mapper**.

```shell
make
```

This will install **restful_mapper** as a static library in the `lib` folder.

## Tests ##

TOWRITE

# Usage #

## API configuration ##

Before making any requests to the web service, it must be configured using the
following methods.

The root URL of the evok web service is specified using the `set_url` method:

```c++
	Api api;
	api.set_url("localhost:80/rest"); //this is the default 
```

If the evok web service is configured for authentication, provide the username and password:

```c++
api.set_username("admin");
api.set_password("test");
```


If you are using a proxy server, it can be specified through the `HTTP_PROXY`
environment variable or using the `set_proxy` method:

See \evokTests for complete examples.

```c++
api.set_proxy("http://myproxy");
```

## Mapper configuration ##

This example illustrates a complete Analog Input object mapping:

```c++
class AI : public Model<AI>
{
public:
	Primary id;
	Field <double> value;
	Field <double> interval;
	
	virtual void map_set(Mapper &mapper) const
	{
		mapper.set("value", value);
		mapper.set("interval", interval);
	}

	virtual void map_get(const Mapper &mapper)
	{
		mapper.get("value", value);
		mapper.get("interval", interval);
	}
	
	virtual std::string endpoint() const
	{
		return "/ai";
	}

	virtual const Primary &primary() const
	{
		return id;
	}
};

```
See \evokMaps for mapping for Digital Input and Relays.

An API entity is declared by creating a class that inherits from and follows the
interface defined in `restful_mapper::Model`.

Each entity can hold a number of fields and relationships:

* `restful_mapper::Primary` -- maps a primary key (integer)
* `restful_mapper::Foreign` -- maps a foreign key (integer)
* `restful_mapper::Field<string>` -- maps a string literal (represented in locale charset)
* `restful_mapper::Field<int>` -- maps an integer value
* `restful_mapper::Field<double>` -- maps a floating point value
* `restful_mapper::Field<bool>` -- maps a boolean value
* `restful_mapper::Field<time_t>` -- maps a datetime value (represented in the local timezone)
* `restful_mapper::HasOne<class>` -- maps a one-to-one or many-to-one relationship on the referenced side
* `restful_mapper::BelongsTo<class>` -- maps a one-to-one or many-to-one relationship on the foreign key side
* `restful_mapper::HasMany<class>` -- maps a one-to-many relationship

The interface specified the following methods, which must be overriden:

* `virtual void restful_mapper::Model::map_set(Mapper &mapper) const`<br/>
  Invoked upon saving an object to the web service.
* `virtual void restful_mapper::Model::map_get(const Mapper &mapper)`<br/>
  Invoked upon requesting an object from the web service.
* `virtual std::string restful_mapper::Model::endpoint() const`<br/>
  Specifies the API endpoint for this particular model. Relative to the web service
  root URL.
* `virtual const Primary &restful_mapper::Model::primary()` const<br/>
  Specifies the primary key of the model.

## Working with objects ##

Using the models defined above, the following operations are made available by
**restful_mapper**.

### Requesting data ###

```c++
	AI ai = AI::find(1, api);	
	double value = ai.value;
	
	See \evokTests for complete examples.
```

### Saving data ###

```c++
	Relay relay = Relay::find(8, api);	
	relay.value = 1;
	relay.save(api);
	
	See \evokTests for complete examples.
```

### Relationships ###
See https://github.com/logandk/restful_mapper

### Querying ###
See https://github.com/logandk/restful_mapper

### Exceptions ###

Some API errors are caught using custom exceptions.

* Internal [libcurl][7] errors are represented as a `restful_mapper::ApiError`,
  which has adds a `code()` method to `std::runtime_error`.
* `restful_mapper::AuthenticationError` is thrown when authentication fails,
  and has the same properties as `restful_mapper::ApiError`.
* `restful_mapper::BadRequestError` is thrown when an error occurs on the API
  side, and has the same properties as `restful_mapper::ApiError`.
* `restful_mapper::ValidationError` is thrown when one or more validation
  errors are thrown by the API. It has the same properties as
  `restful_mapper::ApiError`, but adds an `errors()` method, which returns a
  `restful_mapper::ValidationError::FieldMap` map with field names as keys and
  error messages as values. This map may also be accessed directly through the
  overloaded `operator[]`.

# Contributing #

Pull requests on [GitHub][1] are very welcome! Please try to follow these simple rules:

* Please create a topic branch for every separate change you make.
* Make sure your patches are well tested. All tests must pass on [Travis CI][2].
* Update this [`README.md`](http://github.com/logandk/restful_mapper/blob/master/README.md) if applicable.

# License #

This code is copyright 2013 Logan Raarup, and is released under the revised BSD License.

For more information, see [`LICENSE`](http://github.com/logandk/restful_mapper/blob/master/LICENSE).


[1]: http://github.com/logandk/restful_mapper
[2]: http://travis-ci.org/logandk/restful_mapper
[3]: https://github.com/rails/activeresource
[4]: https://github.com/jfinkels/flask-restless
[5]: https://flask-restless.readthedocs.org/en/latest/requestformat.html
[6]: http://www.cmake.org
[7]: http://curl.haxx.se/libcurl
[8]: http://lloyd.github.io/yajl
[9]: http://www.gnu.org/software/libiconv
[10]: https://code.google.com/p/googletest
[11]: https://flask-restless.readthedocs.org/en/latest/searchformat.html#queryformat
